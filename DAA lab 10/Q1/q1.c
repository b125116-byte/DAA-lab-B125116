#include <stdio.h>
#include <stdlib.h>

int *parent, *parity, *sz;   
int find(int x) {
    if (parent[x] == x) return x;
    int old = parent[x];
    int r = find(old);         
    parity[x] ^= parity[old];  
    parent[x] = r;              
    return r;
}

int main(void) {
    int V, E;
    scanf("%d %d", &V, &E);
    parent = malloc((V + 1) * sizeof(int));
    parity = calloc(V + 1, sizeof(int));
    sz     = malloc((V + 1) * sizeof(int));
    for (int i = 1; i <= V; i++) { parent[i] = i; sz[i] = 1; }

    for (int i = 1; i <= E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        int ru = find(u), rv = find(v);
        if (ru == rv) {
            if (parity[u] == parity[v])
                printf("Edge %d (%d,%d): REJECTED - creates odd cycle\n", i, u, v);
            else
                printf("Edge %d (%d,%d): ACCEPTED (even cycle / already consistent)\n", i, u, v);
        } else {
            if (sz[ru] > sz[rv]) { int t = ru; ru = rv; rv = t; }
            parent[ru] = rv;                         
            parity[ru] = parity[u] ^ parity[v] ^ 1;  
            sz[rv] += sz[ru];
            printf("Edge %d (%d,%d): ACCEPTED (merged two components)\n", i, u, v);
        }
    }
    free(parent); 
  free(parity); 
  free(sz);
    return 0;
}
