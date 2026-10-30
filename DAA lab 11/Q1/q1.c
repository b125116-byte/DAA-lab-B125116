#include <stdio.h>
#include <stdlib.h>
typedef long long ll;
#define INF ((ll)4e18)

int main(void) {
    int n, m, S; ll C;
    if (scanf("%d %d %d %lld", &n, &m, &S, &C) != 4) return 1;
    int *head = malloc(n * sizeof(int)), *nxt = malloc(m * sizeof(int));
    int *to = malloc(m * sizeof(int)), *wt = malloc(m * sizeof(int));
    for (int i = 0; i < n; i++) head[i] = -1;
    for (int i = 0; i < m; i++) {                 /* adjacency list */
        int u, v, w; scanf("%d %d %d", &u, &v, &w);
        u--; v--; to[i] = v; wt[i] = w; nxt[i] = head[u]; head[u] = i;
    }
    int N = 2 * n;                                 /* state id = v*2 + parity */
    ll *dist = malloc(N * sizeof(ll)); char *done = calloc(N, 1);
    for (int i = 0; i < N; i++) dist[i] = INF;
    int K = 2 * m + 3;                             /* max pushes per end */
    int *dq = malloc((2 * K + 2) * sizeof(int));
    int hd = K, tl = K;                            /* deque = dq[hd..tl-1] */
    dist[(S - 1) * 2] = 0; dq[tl++] = (S - 1) * 2;
    while (hd < tl) {
        int x = dq[hd++];
        if (done[x]) continue;
        done[x] = 1;
        int v = x >> 1, p = x & 1;
        for (int e = head[v]; e != -1; e = nxt[e]) {
            int y = to[e] * 2 + (p ^ wt[e]);       /* weight-1 edge flips parity */
            if (dist[x] + wt[e] < dist[y]) {
                dist[y] = dist[x] + wt[e];
                if (wt[e] == 0) dq[--hd] = y; else dq[tl++] = y;
            }
        }
    }
    for (int v = 0; v < n; v++) {
        ll a = dist[2 * v], b = dist[2 * v + 1];
        ll best = a;                                /* even k1: no penalty */
        if (b < INF && b + C < best) best = b + C;  /* odd k1: add C */
        if (best >= INF) printf("%d: UNREACHABLE\n", v + 1);
        else printf("%d: %lld\n", v + 1, best);
    }
    return 0;
}
