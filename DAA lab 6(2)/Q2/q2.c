#include <stdio.h>
#include <stdlib.h>
static int max(int a, int b) { return a > b ? a : b; }
int main(void) {
    int n, W;
    if (scanf("%d %d", &n, &W) != 2) return 1;
    int *wt = malloc(n * sizeof(int)), *pr = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) scanf("%d", &wt[i]);
    for (int i = 0; i < n; i++) scanf("%d", &pr[i]);
    int **dp = malloc((n + 1) * sizeof(int *));
    for (int i = 0; i <= n; i++) dp[i] = calloc(W + 1, sizeof(int));
    for (int i = 1; i <= n; i++)
        for (int w = 0; w <= W; w++) {
            dp[i][w] = dp[i - 1][w];                              /* skip item i */
            if (wt[i - 1] <= w)                                   /* take item i */
                dp[i][w] = max(dp[i][w], dp[i - 1][w - wt[i - 1]] + pr[i - 1]);
        }
    printf("Maximum profit = %d\nItems chosen:", dp[n][W]);
    for (int i = n, w = W; i > 0; i--)                            /* backtrack */
        if (dp[i][w] != dp[i - 1][w]) { printf(" %d", i); w -= wt[i - 1]; }
    printf("\n");
    return 0;
}
