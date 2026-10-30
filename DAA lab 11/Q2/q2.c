#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m, K, R;
    if (scanf("%d %d %d %d", &n, &m, &K, &R) != 4) return 1;
    int *hubs = malloc(K * sizeof(int));
    for (int i = 0; i < K; i++) { scanf("%d", &hubs[i]); hubs[i]--; }
    int *head = malloc(n * sizeof(int)), *nxt = malloc(2 * m * sizeof(int)), *to = malloc(2 * m * sizeof(int));
    for (int i = 0; i < n; i++) head[i] = -1;
    int ec = 0;
    for (int i = 0; i < m; i++) {
        int u, v; scanf("%d %d", &u, &v); u--; v--;
        to[ec] = v; nxt[ec] = head[u]; head[u] = ec++;
        to[ec] = u; nxt[ec] = head[v]; head[v] = ec++;
    }
    int *dist = malloc(n * sizeof(int)), *owner = malloc(n * sizeof(int)), *q = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) { dist[i] = -1; owner[i] = -1; }
    int qh = 0, qt = 0;
    for (int i = 0; i < K; i++) {                  /* enqueue all hubs at distance 0 */
        int h = hubs[i];
        if (dist[h] == -1) { dist[h] = 0; owner[h] = i + 1; q[qt++] = h; }
    }                                              /* duplicate hub vertex: smaller index kept */
    while (qh < qt) {
        int v = q[qh++];
        if (dist[v] == R) continue;                /* radius reached: do not expand */
        for (int e = head[v]; e != -1; e = nxt[e]) {
            int u = to[e];
            if (dist[u] == -1) {
                dist[u] = dist[v] + 1; owner[u] = owner[v]; q[qt++] = u;
            } else if (dist[u] == dist[v] + 1 && owner[v] < owner[u]) {
                owner[u] = owner[v];               /* tie-break: smallest hub index */
            }
        }
    }
    for (int v = 0; v < n; v++)
        printf("%d: owner=%d dist=%d\n", v + 1, owner[v], owner[v] == -1 ? -1 : dist[v]);
    return 0;
}
