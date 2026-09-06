#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct { double re, im; } Complex;

Complex cadd(Complex a, Complex b) { Complex r = {a.re + b.re, a.im + b.im}; return r; }
Complex csub(Complex a, Complex b) { Complex r = {a.re - b.re, a.im - b.im}; return r; }
Complex cmul(Complex a, Complex b) {
    Complex r = { a.re * b.re - a.im * b.im, a.re * b.im + a.im * b.re };
    return r;
}


void fft(Complex *a, int N, int invert) {
    if (N == 1) return;

    Complex *even = malloc((N / 2) * sizeof(Complex));
    Complex *odd  = malloc((N / 2) * sizeof(Complex));
    for (int i = 0; i < N / 2; i++) { even[i] = a[2 * i]; odd[i] = a[2 * i + 1]; }

    fft(even, N / 2, invert);   /* T(N/2) */
    fft(odd,  N / 2, invert);   /* T(N/2) */

    double ang = 2 * M_PI / N * (invert ? -1 : 1);
    Complex w = {1, 0}, wn = {cos(ang), sin(ang)};
    for (int i = 0; i < N / 2; i++) {          /* O(N) combine step */
        Complex t = cmul(w, odd[i]);
        a[i]         = cadd(even[i], t);
        a[i + N / 2] = csub(even[i], t);
        w = cmul(w, wn);
    }
    free(even); free(odd);
    /* T(N) = 2T(N/2) + O(N)  =>  T(N) = O(N log N) */
}

int nextPow2(int x) { int p = 1; while (p < x) p <<= 1; return p; }


void convolveFFT(double *A, int m, double *B, int n, double *C /* size m+n-1 */) {
    int resultLen = m + n - 1;
    int N = nextPow2(resultLen);

    Complex *fa = malloc(N * sizeof(Complex));
    Complex *fb = malloc(N * sizeof(Complex));
    for (int i = 0; i < N; i++) {
        fa[i].re = (i < m) ? A[i] : 0.0; fa[i].im = 0.0;
        fb[i].re = (i < n) ? B[i] : 0.0; fb[i].im = 0.0;
    }

    fft(fa, N, 0);              /* evaluate p at N-th roots of unity */
    fft(fb, N, 0);              /* evaluate q at N-th roots of unity */
    for (int i = 0; i < N; i++) fa[i] = cmul(fa[i], fb[i]); /* pointwise, O(N) */
    fft(fa, N, 1);              /* interpolate back (inverse FFT) */

    for (int i = 0; i < resultLen; i++) C[i] = fa[i].re / N;

    free(fa); free(fb);
}


void convolveBrute(double *A, int m, double *B, int n, double *C) {
    int resultLen = m + n - 1;
    for (int k = 0; k < resultLen; k++) {
        C[k] = 0;
        for (int j = 0; j < m; j++)
            if (k - j >= 0 && k - j < n) C[k] += A[j] * B[k - j];
    }
}

int main(void) {
    int m, n;
    printf("Enter length of A (m): "); scanf("%d", &m);
    double *A = malloc(m * sizeof(double));
    printf("Enter %d elements of A: ", m);
    for (int i = 0; i < m; i++) scanf("%lf", &A[i]);

    printf("Enter length of B (n), n >= m: "); scanf("%d", &n);
    if (n < m) { printf("Requirement n >= m violated.\n"); return 1; }
    double *B = malloc(n * sizeof(double));
    printf("Enter %d elements of B: ", n);
    for (int i = 0; i < n; i++) scanf("%lf", &B[i]);

    int resultLen = m + n - 1;
    double *C1 = malloc(resultLen * sizeof(double));
    double *C2 = malloc(resultLen * sizeof(double));

    convolveFFT(A, m, B, n, C1);
    convolveBrute(A, m, B, n, C2);

    printf("\nConvolution (FFT, O(n log n)):\n");
    for (int i = 0; i < resultLen; i++) printf("%.4f ", C1[i]);
    printf("\n\nConvolution (brute force, O(mn), for verification):\n");
    for (int i = 0; i < resultLen; i++) printf("%.4f ", C2[i]);
    printf("\n");

    free(A); free(B); free(C1); free(C2);
    return 0;
}
