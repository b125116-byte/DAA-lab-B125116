#include <stdio.h>
#include <stdlib.h>
static void print_rev(int *a, int *par, int i){ if (i < 0) return; print_rev(a, par, par[i]); printf("%d ", a[i]); }
int main(){
    int n;
    if (scanf("%d", &n) != 1) 
      return 1;
    int *a = malloc(n * sizeof(int)), *dp = malloc(n * sizeof(int)), *par = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    int best = 0, bi = -1;
    for (int i = 0; i < n; i++) {
        dp[i] = 1; par[i] = -1;
        for (int j = 0; j < i; j++)
            if (a[j] < a[i] && dp[j] + 1 > dp[i]) { dp[i] = dp[j] + 1; par[i] = j; }
        if (dp[i] > best) { best = dp[i]; bi = i; }
    }
    printf("LIS length (O(n^2) DP) = %d\nOne LIS: ", best);
    print_rev(a, par, bi); 
  printf("\n");

    int *t = malloc(n * sizeof(int)), len = 0;
    for (int i = 0; i < n; i++) {
        int lo = 0, hi = len;                 
        while (lo < hi) { int mid = (lo + hi) / 2; if (t[mid] < a[i]) lo = mid + 1; else hi = mid; }
        t[lo] = a[i]; if (lo == len) len++;
    }
    printf("LIS length (O(n log n)) = %d\n", len);
    free(a); 
  free(dp); 
  free(par); 
  free(t);
    return 0;
}
