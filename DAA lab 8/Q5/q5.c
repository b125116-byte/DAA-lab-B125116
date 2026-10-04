#include <stdio.h>
#include <stdlib.h>
static void print_rev(int *a, int *par, int i){ if (i < 0) return; print_rev(a, par, par[i]); printf("%d ", a[i]); }
int main(){
    int n;
    if (scanf("%d", &n) != 1) 
      return 1;
    int *a = malloc(n * sizeof(int)), *par = malloc(n * sizeof(int));
    long long *S = malloc(n * sizeof(long long));
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    long long best = 0; int bi = -1;
    for (int i = 0; i < n; i++) {
        S[i] = a[i]; par[i] = -1;
        for (int j = 0; j < i; j++)
            if (a[j] < a[i] && S[j] + a[i] > S[i]) { S[i] = S[j] + a[i]; par[i] = j; }
        if (S[i] > best) { best = S[i]; bi = i; }
    }
    printf("Max sum = %lld\nSubsequence: ", best);
    print_rev(a, par, bi); printf("\n");
    free(a); 
  free(par); 
  free(S);
    return 0;
}
