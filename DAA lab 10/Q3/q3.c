#include <stdio.h>
#include <stdlib.h>

typedef struct { long long w; int r, s; } Item;

int *parent, *sz;
long long *sum;
Item *heap; int hn = 0;

int find(int x) {
    while (parent[x] != x) { parent[x] = parent[parent[x]]; x = parent[x]; }
    return x;
}
void push(Item x) {
    int i = hn++;
    heap[i] = x;
    while (i > 0 && heap[(i - 1) / 2].w < heap[i].w) {
        Item t = heap[i]; heap[i] = heap[(i - 1) / 2]; heap[(i - 1) / 2] = t;
        i = (i - 1) / 2;
    }
}
void pop(void) {
    heap[0] = heap[--hn];
    int i = 0;
    for (;;) {
        int l = 2 * i + 1, r = l + 1, m = i;
        if (l < hn && heap[l].w > heap[m].w) m = l;
        if (r < hn && heap[r].w > heap[m].w) m = r;
        if (m == i) break;
        Item t = heap[i]; heap[i] = heap[m]; heap[m] = t;
        i = m;
    }
}

int main() {
    int V, E, K;
    scanf("%d %d %d", &V, &E, &K);
    parent = malloc((V + 1) * sizeof(int));
    sz     = malloc((V + 1) * sizeof(int));
    sum    = malloc((V + 1) * sizeof(long long));
    heap   = malloc((2 * V + 2) * sizeof(Item));     
    for (int i = 1; i <= V; i++) {
        scanf("%lld", &sum[i]);
        parent[i] = i; sz[i] = 1;
        if (1 <= K) push((Item){sum[i], i, 1});
    }
    for (int i = 1; i <= E; i++) {
        int u, v; long long wt;
        scanf("%d %d %lld", &u, &v, &wt);
        int a = find(u), b = find(v);
        if (a != b) {
            if (sz[a] < sz[b]) { int t = a; a = b; b = t; }
            parent[b] = a; sz[a] += sz[b]; sum[a] += sum[b];
            if (sz[a] <= K) push((Item){sum[a], a, sz[a]});
        }
        
        while (hn > 0) {
            Item t = heap[0];
            if (parent[t.r] == t.r && sz[t.r] == t.s && t.s <= K) break;
            pop();
        }
        if (hn > 0) printf("After edge %d: %lld\n", i, heap[0].w);
        else        printf("After edge %d: none (no component of size <= K)\n", i);
    }
    return 0;
}
