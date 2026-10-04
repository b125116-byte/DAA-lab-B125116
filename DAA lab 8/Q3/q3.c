#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define L(i,j) L[(i)*(n+1)+(j)]
int main(){
    static char X[10001], Y[10001];
    if (scanf("%10000s %10000s", X, Y) != 2) 
      return 1;
    int m = strlen(X), n = strlen(Y);
    int *L = calloc((m + 1) * (n + 1), sizeof(int));
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            L(i,j) = (X[i-1] == Y[j-1]) ? L(i-1,j-1) + 1
                   : (L(i-1,j) >= L(i,j-1) ? L(i-1,j) : L(i,j-1));
    int len = L(m,n);
    char *s = malloc(len + 1); s[len] = '\0';
    int i = m, j = n, k = len;
    while (i > 0 && j > 0) {
        if (X[i-1] == Y[j-1]) { s[--k] = X[i-1]; i--; j--; }
        else if (L(i-1,j) >= L(i,j-1)) i--;
        else j--;
    }
    printf("LCS length = %d\nLCS        = %s\n", len, s);
    free(L); 
  free(s);
    return 0;
}
