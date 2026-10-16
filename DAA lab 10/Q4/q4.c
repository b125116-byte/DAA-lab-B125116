#include <stdio.h>
#include <stdlib.h>

int *parent, *sz, *head, *nxt, *to, *active;
long long *sum;

int find(int x) {
    while (parent[x] != x) { parent[x] = parent[parent[x]]; x = parent[x]; }
    return x;
}
void unite(int a, int b) {
    a = find(a); b = find(b);
    if (a == b) return;
    if (sz[a] < sz[b]) { int t = a; a = b; b = t; }
    parent[b] = a; sz[a] += sz[b]; sum[a] += sum[b];
}

int main() {
    int V, E;
    scanf("%d %d", &V, &E);
    parent = malloc((V + 1) * sizeof(int));
    sz     = malloc((V + 1) * sizeof(int));
    head   = malloc((V + 1) * sizeof(int));
    active = calloc(V + 1, sizeof(int));
    nxt    = malloc(2 * E * sizeof(int));
    to     = malloc(2 * E * sizeof(int));
    sum    = malloc((V + 1) * sizeof(long long));
    int *P = malloc((V + 1) * sizeof(int));
    long long *ans = malloc((V + 1) * sizeof(long long));

    for (int i = 1; i <= V; i++) { scanf("%lld", &sum[i]); head[i] = -1; parent[i] = i; sz[i] = 1; }
    int ec = 0;                                   
    for (int i = 0; i < E; i++) {
        int u, v; scanf("%d %d", &u, &v);
        to[ec] = v; nxt[ec] = head[u]; head[u] = ec++;
        to[ec] = u; nxt[ec] = head[v]; head[v] = ec++;
    }
    for (int i = 1; i <= V; i++) scanf("%d", &P[i]);

    long long best = 0;
    for (int i = V; i >= 1; i--) {
        ans[i] = best;                
        int v = P[i];
        active[v] = 1;                 
        for (int e = head[v]; e != -1; e = nxt[e])
            if (active[to[e]]) unite(v, to[e]);
        long long s = sum[find(v)];
        if (s > best) best = s;        
    }
    for (int i = 1; i <= V; i++) printf("After deleting p%d (vertex %d): %lld\n", i, P[i], ans[i]);
    return 0;
}
