#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(void) {
    char X[1001], Y[1001];
    if (scanf("%1000s %1000s", X, Y) != 2) return 1;
    int m = strlen(X), n = strlen(Y);
    int (*L)[1001] = calloc(m + 1, sizeof *L);
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            if (X[i - 1] == Y[j - 1]) L[i][j] = L[i - 1][j - 1] + 1;
            else L[i][j] = L[i - 1][j] > L[i][j - 1] ? L[i - 1][j] : L[i][j - 1];
    int len = L[m][n];
    char *lcs = malloc(len + 1); lcs[len] = '\0';
    int i = m, j = n, k = len;
    while (i > 0 && j > 0) {                                      /* backtrack */
        if (X[i - 1] == Y[j - 1]) { lcs[--k] = X[i - 1]; i--; j--; }
        else if (L[i - 1][j] >= L[i][j - 1]) i--;
        else j--;
    }
    printf("LCS length = %d\nLCS = %s\n", len, lcs);
    return 0;
}
