#include <stdio.h>
#include <stdlib.h>

int **allocMat(int n) {
    int **m = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) m[i] = calloc(n, sizeof(int));
    return m;
}

void freeMat(int **m, int n) {
    for (int i = 0; i < n; i++) free(m[i]);
    free(m);
}

void addMat(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void subMat(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

void strassen(int **A, int **B, int **C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }
    int k = n / 2;
    int **A11 = allocMat(k), **A12 = allocMat(k), **A21 = allocMat(k), **A22 = allocMat(k);
    int **B11 = allocMat(k), **B12 = allocMat(k), **B21 = allocMat(k), **B22 = allocMat(k);

    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++) {
            A11[i][j] = A[i][j];         A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];     A22[i][j] = A[i + k][j + k];
            B11[i][j] = B[i][j];         B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];     B22[i][j] = B[i + k][j + k];
        }

    int **M1 = allocMat(k), **M2 = allocMat(k), **M3 = allocMat(k), **M4 = allocMat(k);
    int **M5 = allocMat(k), **M6 = allocMat(k), **M7 = allocMat(k);
    int **T1 = allocMat(k), **T2 = allocMat(k);

    addMat(A11, A22, T1, k); addMat(B11, B22, T2, k); strassen(T1, T2, M1, k);
    addMat(A21, A22, T1, k);                          strassen(T1, B11, M2, k);
    subMat(B12, B22, T2, k);                          strassen(A11, T2, M3, k);
    subMat(B21, B11, T2, k);                          strassen(A22, T2, M4, k);
    addMat(A11, A12, T1, k);                          strassen(T1, B22, M5, k);
    subMat(A21, A11, T1, k); addMat(B11, B12, T2, k); strassen(T1, T2, M6, k);
    subMat(A12, A22, T1, k); addMat(B21, B22, T2, k); strassen(T1, T2, M7, k);

    int **C11 = allocMat(k), **C12 = allocMat(k), **C21 = allocMat(k), **C22 = allocMat(k);
    addMat(M1, M4, T1, k); subMat(T1, M5, T2, k); addMat(T2, M7, C11, k); /* M1+M4-M5+M7 */
    addMat(M3, M5, C12, k);                                              /* M3+M5       */
    addMat(M2, M4, C21, k);                                              /* M2+M4       */
    subMat(M1, M2, T1, k); addMat(T1, M3, T2, k); addMat(T2, M6, C22, k); /* M1-M2+M3+M6 */

    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++) {
            C[i][j] = C11[i][j];         C[i][j + k] = C12[i][j];
            C[i + k][j] = C21[i][j];     C[i + k][j + k] = C22[i][j];
        }

    freeMat(A11, k); freeMat(A12, k); freeMat(A21, k); freeMat(A22, k);
    freeMat(B11, k); freeMat(B12, k); freeMat(B21, k); freeMat(B22, k);
    freeMat(M1, k); freeMat(M2, k); freeMat(M3, k); freeMat(M4, k);
    freeMat(M5, k); freeMat(M6, k); freeMat(M7, k);
    freeMat(T1, k); freeMat(T2, k);
    freeMat(C11, k); freeMat(C12, k); freeMat(C21, k); freeMat(C22, k);
}

int main() {
    int n;
    printf("Enter size n (must be a power of 2): ");
    scanf("%d", &n);
    int **A = allocMat(n), **B = allocMat(n), **C = allocMat(n);

    printf("Enter matrix A (%d x %d):\n", n, n);
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) scanf("%d", &A[i][j]);
    printf("Enter matrix B (%d x %d):\n", n, n);
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) scanf("%d", &B[i][j]);

    strassen(A, B, C, n);

    printf("\nResult matrix C = A x B:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) printf("%d ", C[i][j]);
        printf("\n");
    }

    freeMat(A, n); freeMat(B, n); freeMat(C, n);
    return 0;
}
