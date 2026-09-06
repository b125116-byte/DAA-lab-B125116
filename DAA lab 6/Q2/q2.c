#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int** allocMat(int n) {
    int **M = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) M[i] = malloc(n * sizeof(int));
    return M;
}
void freeMat(int **M, int n) { for (int i = 0; i < n; i++) free(M[i]); free(M); }
void readMat(int **M, int n) { for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) scanf("%d", &M[i][j]); }
void printMat(int **M, int n) {
    for (int i = 0; i < n; i++) { for (int j = 0; j < n; j++) printf("%d ", M[i][j]); printf("\n"); }
}


void matAdd(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}


void matMul(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            int sum = 0;
            for (int k = 0; k < n; k++) sum += A[i][k] * B[k][j];
            C[i][j] = sum;
        }
}


int isZero(int **A, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (A[i][j] != 0) return 0;
    return 1;
}


int isSymmetric(int **A, int n) {
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (A[i][j] != A[j][i]) return 0;
    return 1;
}


double determinant(int **A, int n) {
    double **M = malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        M[i] = malloc(n * sizeof(double));
        for (int j = 0; j < n; j++) M[i][j] = A[i][j];
    }
    double det = 1.0;
    for (int i = 0; i < n; i++) {
        int pivot = i;
        for (int k = i + 1; k < n; k++)
            if (fabs(M[k][i]) > fabs(M[pivot][i])) pivot = k;
        if (fabs(M[pivot][i]) < 1e-12) { det = 0; break; }
        if (pivot != i) { double *t = M[i]; M[i] = M[pivot]; M[pivot] = t; det = -det; }
        det *= M[i][i];
        for (int k = i + 1; k < n; k++) {
            double factor = M[k][i] / M[i][i];
            for (int j = i; j < n; j++) M[k][j] -= factor * M[i][j];
        }
    }
    for (int i = 0; i < n; i++) free(M[i]);
    free(M);
    return det;
}


void transposeInPlace(int **A, int n) {
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) {
            int t = A[i][j]; A[i][j] = A[j][i]; A[j][i] = t;
        }
}


void powerIteration(int **A, int n, double *eigenvalue, double *vec, int iterations) {
    double *v = malloc(n * sizeof(double));
    double *vnew = malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) v[i] = 1.0;

    for (int it = 0; it < iterations; it++) {
        for (int i = 0; i < n; i++) {
            vnew[i] = 0;
            for (int j = 0; j < n; j++) vnew[i] += A[i][j] * v[j];
        }
        double norm = 0;
        for (int i = 0; i < n; i++) norm += vnew[i] * vnew[i];
        norm = sqrt(norm);
        if (norm < 1e-12) break;
        for (int i = 0; i < n; i++) v[i] = vnew[i] / norm;
    }

  
    double num = 0, den = 0;
    for (int i = 0; i < n; i++) {
        double Avi = 0;
        for (int j = 0; j < n; j++) Avi += A[i][j] * v[j];
        num += v[i] * Avi;
        den += v[i] * v[i];
    }
    *eigenvalue = num / den;
    for (int i = 0; i < n; i++) vec[i] = v[i];
    free(v); free(vnew);
}

int main(void) {
    int n;
    printf("Enter n (matrix size): ");
    scanf("%d", &n);

    int **A = allocMat(n), **B = allocMat(n), **C = allocMat(n);
    printf("Enter matrix A (%d x %d):\n", n, n); readMat(A, n);
    printf("Enter matrix B (%d x %d):\n", n, n); readMat(B, n);

    matAdd(A, B, C, n);
    printf("\n(i) A+B:\n"); printMat(C, n);

    matMul(A, B, C, n);
    printf("\n(ii) A*B:\n"); printMat(C, n);

    printf("\n(iii) A is zero matrix? %s\n", isZero(A, n) ? "Yes" : "No");
    printf("(iv)  A is symmetric?   %s\n", isSymmetric(A, n) ? "Yes" : "No");
    printf("(v)   det(A) = %.4f\n", determinant(A, n));

    transposeInPlace(A, n);
    printf("\n(vi) A transposed:\n"); printMat(A, n);
    transposeInPlace(A, n); /* restore original for the next step */

    double eigVal;
    double *eigVec = malloc(n * sizeof(double));
    powerIteration(A, n, &eigVal, eigVec, 200);
    printf("\n(vii) Dominant eigenvalue  ~ %.4f\n", eigVal);
    printf("      Dominant eigenvector ~ ");
    for (int i = 0; i < n; i++) printf("%.4f ", eigVec[i]);
    printf("\n");

    freeMat(A, n); freeMat(B, n); freeMat(C, n); free(eigVec);
    return 0;
}
