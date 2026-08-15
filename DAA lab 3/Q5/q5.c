#include <stdio.h>
#include <stdlib.h>

int **allocMat(int n) {
    int **m = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) m[i] = calloc(n, sizeof(int));
    return m;
}
void freeMat(int **m, int n) { 
  for (int i = 0; i < n; i++) 
  free(m[i]); 
  free(m); 
}

void addMat(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) C[i][j] = A[i][j] + B[i][j];
}
void subMat(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) C[i][j] = A[i][j] - B[i][j];
}

/* Multiplies two n x n matrices A, B that both have the recursive pattern
   M = [[X, Y], [Y, X]] at every level down to single elements (n = 2^k).
   Trick: let P = X+Y, Q = X-Y (top row blocks). Then for A*B = [[C1,C2],[C2,C1]]:
     C1 = A1*B1 + A2*B2 = (PA*PB + QA*QB) / 2
     C2 = A1*B2 + A2*B1 = (PA*PB - QA*QB) / 2
   PA, QA, PB, QB again have the same [[X,Y],[Y,X]] pattern, so we recurse.
   Recurrence: T(n) = 2T(n/2) + O(n^2)  =>  T(n) = O(n^2). */
void specialMultiply(int **A, int **B, int **C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }
    int k = n / 2;
    int **A11 = allocMat(k), **A12 = allocMat(k);
    int **B11 = allocMat(k), **B12 = allocMat(k);
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++) {
            A11[i][j] = A[i][j]; A12[i][j] = A[i][j + k];
            B11[i][j] = B[i][j]; B12[i][j] = B[i][j + k];
        }

    int **PA = allocMat(k), **QA = allocMat(k), **PB = allocMat(k), **QB = allocMat(k);
    addMat(A11, A12, PA, k); subMat(A11, A12, QA, k);
    addMat(B11, B12, PB, k); subMat(B11, B12, QB, k);

    int **PC = allocMat(k), **QC = allocMat(k);
    specialMultiply(PA, PB, PC, k);
    specialMultiply(QA, QB, QC, k);

    int **C1 = allocMat(k), **C2 = allocMat(k), **T = allocMat(k);
    addMat(PC, QC, T, k);
    for (int i = 0; i < k; i++) for (int j = 0; j < k; j++) C1[i][j] = T[i][j] / 2;
    subMat(PC, QC, T, k);
    for (int i = 0; i < k; i++) for (int j = 0; j < k; j++) C2[i][j] = T[i][j] / 2;

    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++) {
            C[i][j] = C1[i][j];       C[i][j + k] = C2[i][j];
            C[i + k][j] = C2[i][j];   C[i + k][j + k] = C1[i][j];
        }

    freeMat(A11, k); freeMat(A12, k); freeMat(B11, k); freeMat(B12, k);
    freeMat(PA, k); freeMat(QA, k); freeMat(PB, k); freeMat(QB, k);
    freeMat(PC, k); freeMat(QC, k); freeMat(C1, k); freeMat(C2, k); freeMat(T, k);
}

int main() {
    int n;
    printf("Enter n (power of 2): ");
    scanf("%d", &n);
    int **A = allocMat(n), **B = allocMat(n), **C = allocMat(n);

    printf("Enter matrix A (%d x %d). Must satisfy the pattern M=[[X,Y],[Y,X]]\n", n, n);
    printf("recursively at every level, e.g. build it from a top-left quadrant X\n");
    printf("and top-right quadrant Y that repeat into the bottom row swapped:\n");
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) scanf("%d", &A[i][j]);
    printf("Enter matrix B (%d x %d) with the same pattern:\n", n, n);
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) scanf("%d", &B[i][j]);

    specialMultiply(A, B, C, n);

    printf("\nResult C = A x B:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) printf("%d ", C[i][j]);
        printf("\n");
    }

    freeMat(A, n); freeMat(B, n); freeMat(C, n);
    return 0;
}
