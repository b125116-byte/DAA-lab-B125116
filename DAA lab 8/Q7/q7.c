#include <stdio.h>
#include <stdlib.h>
int main(){
    int n;
    if (scanf("%d", &n) != 1) 
      return 1;
    int *p = malloc((n + 1) * sizeof(int)), *r = malloc((n + 1) * sizeof(int)), *cut = malloc((n + 1) * sizeof(int));
    for (int i = 1; i <= n; i++) scanf("%d", &p[i]);
    r[0] = 0;
    for (int j = 1; j <= n; j++) {
        r[j] = -1;
        for (int i = 1; i <= j; i++)
            if (p[i] + r[j - i] > r[j]) { r[j] = p[i] + r[j - i]; cut[j] = i; }
    }
    printf("Maximum revenue = %d\nPieces: ", r[n]);
    for (int j = n; j > 0; j -= cut[j]) printf("%d ", cut[j]);
    printf("\n");
    free(p); 
  free(r); 
  free(cut);
    return 0;
}
