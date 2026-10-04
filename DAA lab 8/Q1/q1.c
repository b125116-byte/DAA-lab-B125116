#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
int main(void){
    int n, V;
    if (scanf("%d", &n) != 1) return 1;
    int *c = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) scanf("%d", &c[i]);
    scanf("%d", &V);
    int *dp = malloc((V + 1) * sizeof(int)), *used = malloc((V + 1) * sizeof(int));
    dp[0] = 0;
    for (int v = 1; v <= V; v++) {
        dp[v] = INT_MAX; used[v] = -1;
        for (int i = 0; i < n; i++)
            if (c[i] > 0 && c[i] <= v && dp[v - c[i]] != INT_MAX && dp[v - c[i]] + 1 < dp[v]) {
                dp[v] = dp[v - c[i]] + 1; used[v] = c[i];
            }
    }
    if (dp[V] == INT_MAX) { printf("-1\n"); }
    else {
        printf("Minimum coins = %d\nCoins used: ", dp[V]);
        for (int v = V; v > 0; v -= used[v]) printf("%d ", used[v]);
        printf("\n");
    }
    free(c); 
  free(dp); 
  free(used);
    return 0;
}
