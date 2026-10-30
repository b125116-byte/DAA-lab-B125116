#include <stdio.h>
#include <limits.h>
#define MAX 105
long long m[MAX][MAX]; int s[MAX][MAX];
static void paren(int i, int j) {
    if (i == j) printf("A%d", i);
    else { printf("("); paren(i, s[i][j]); printf(" x "); paren(s[i][j] + 1, j); printf(")"); }
}
int main(void) {
    int N, arr[MAX];
    if (scanf("%d", &N) != 1 || N < 2 || N > 100) return 1;
    for (int i = 0; i < N; i++) scanf("%d", &arr[i]);
    int n = N - 1;                                                /* number of matrices */
    for (int i = 1; i <= n; i++) m[i][i] = 0;
    for (int len = 2; len <= n; len++)                            /* chain length */
        for (int i = 1; i + len - 1 <= n; i++) {
            int j = i + len - 1;
            m[i][j] = LLONG_MAX;
            for (int k = i; k < j; k++) {                         /* split point */
                long long c = m[i][k] + m[k + 1][j] + (long long)arr[i - 1] * arr[k] * arr[j];
                if (c < m[i][j]) { m[i][j] = c; s[i][j] = k; }
            }
        }
    printf("Minimum multiplications = %lld\nOrder: ", m[1][n]);
    paren(1, n); printf("\n");
    return 0;
}
