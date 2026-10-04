#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define D(i,j) D[(i)*(n+1)+(j)]
static int min3(int a,int b,int c){ int m=a<b?a:b; return m<c?m:c; }
int main(){
    static char A[5001], B[5001];
    if (scanf("%5000s %5000s", A, B) != 2) return 1;
    int m = strlen(A), n = strlen(B);
    int *D = malloc((m + 1) * (n + 1) * sizeof(int));
    for (int i = 0; i <= m; i++) D(i,0) = i;
    for (int j = 0; j <= n; j++) D(0,j) = j;
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            D(i,j) = (A[i-1] == B[j-1]) ? D(i-1,j-1)
                   : 1 + min3(D(i-1,j-1), D(i-1,j), D(i,j-1));
    printf("Edit distance = %d\n", D(m,n));

    char **ops = malloc((m + n + 1) * sizeof(char*)); int k = 0;
    int i = m, j = n;
    while (i > 0 || j > 0) {
        char *buf = malloc(64);
        if (i > 0 && j > 0 && A[i-1] == B[j-1] && D(i,j) == D(i-1,j-1))
            { sprintf(buf, "Match   '%c'", A[i-1]); i--; j--; }
        else if (i > 0 && j > 0 && D(i,j) == D(i-1,j-1) + 1)
            { sprintf(buf, "Replace '%c' -> '%c'", A[i-1], B[j-1]); i--; j--; }
        else if (i > 0 && D(i,j) == D(i-1,j) + 1)
            { sprintf(buf, "Delete  '%c'", A[i-1]); i--; }
        else
            { sprintf(buf, "Insert  '%c'", B[j-1]); j--; }
        ops[k++] = buf;
    }
    printf("Traceback (start -> end):\n");
    for (int t = k - 1; t >= 0; t--) { printf("  %s\n", ops[t]); free(ops[t]); }
    free(ops); 
  free(D);
    return 0;
}
