#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int split[50][50];

void print_parens(int i, int j) {
    if (i == j) { printf("A%d", i); return; }
    printf("(");
    print_parens(i, split[i][j]);
    print_parens(split[i][j] + 1, j);
    printf(")");
}

int main() {
    
    int p[] = {30, 35, 15, 5, 10, 20, 25};   /* p[0..k], k = 6 matrices */
    int k = sizeof(p) / sizeof(p[0]) - 1;

    long m[50][50] = {0};

    /* len = chain length being solved, from 2 matrices up to k matrices */
    for (int len = 2; len <= k; len++) {
        for (int i = 1; i <= k - len + 1; i++) {
            int j = i + len - 1;
            m[i][j] = LONG_MAX;
            for (int s = i; s < j; s++) {
                long cost = m[i][s] + m[s + 1][j] + (long)p[i - 1] * p[s] * p[j];
                if (cost < m[i][j]) { m[i][j] = cost; split[i][j] = s; }
            }
        }
    }

    printf("Matrix dimensions p[0..%d]: ", k);
    for (int i = 0; i <= k; i++) printf("%d ", p[i]);
    printf("\n(i.e. A%d is %dx%d, A%d is %dx%d, ...)\n\n", 1, p[0], p[1], 2, p[1], p[2]);

    printf("Minimum number of scalar multiplications: %ld\n", m[1][k]);
    printf("Optimal parenthesization: ");
    print_parens(1, k);
    printf("\n");

    return 0;
}
