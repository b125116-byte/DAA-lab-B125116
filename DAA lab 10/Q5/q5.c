#include <stdio.h>
#include <stdlib.h>

typedef struct { int root, key; } Pair;   

int *parent, *sz;

int find(int x) {
    while (parent[x] != x) { parent[x] = parent[parent[x]]; x = parent[x]; }
    return x;
}
int cmp(const void *a, const void *b) {
    const Pair *x = a, *y = b;
    if (x->root != y->root) return x->root - y->root;
    return x->key - y->key;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int *A = malloc((n + 1) * sizeof(int));
    parent = malloc((n + 1) * sizeof(int));
    sz     = malloc((n + 1) * sizeof(int));
    for (int i = 1; i <= n; i++) { scanf("%d", &A[i]); parent[i] = i; sz[i] = 1; }
    for (int i = 0; i < m; i++) {
        int u, v; scanf("%d %d", &u, &v);
        int a = find(u), b = find(v);
        if (a == b) continue;
        if (sz[a] < sz[b]) { int t = a; a = b; b = t; }
        parent[b] = a; sz[a] += sz[b];
    }
    Pair *vals = malloc(n * sizeof(Pair)), *pos = malloc(n * sizeof(Pair));
    for (int i = 1; i <= n; i++) {
        int r = find(i);
        vals[i - 1] = (Pair){r, A[i]};   
        pos[i - 1]  = (Pair){r, i};      
    }
    qsort(vals, n, sizeof(Pair), cmp);   
    qsort(pos,  n, sizeof(Pair), cmp);   
    int *res = malloc((n + 1) * sizeof(int));
    for (int i = 0; i < n; i++) res[pos[i].key] = vals[i].key;  
    for (int i = 1; i <= n; i++) printf("%d ", res[i]);
    printf("\n");
    return 0;
}
