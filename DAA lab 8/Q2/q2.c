#include <stdio.h>
#include <stdlib.h>
int main(){
    int n, V;
    if (scanf("%d", &n) != 1) 
      return 1;
    int *c = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) scanf("%d", &c[i]);
    scanf("%d", &V);
    unsigned long long *w = calloc(V + 1, sizeof(unsigned long long));
    w[0] = 1;
    for (int i = 0; i < n; i++)
        for (int v = c[i]; v <= V; v++) w[v] += w[v - c[i]];
    printf("Number of ways = %llu\n", w[V]);
    free(c); 
  free(w);
    return 0;
}
