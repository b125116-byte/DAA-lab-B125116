#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { char p[12]; int id; int pos; } Entry;
static int cmp(const void *a, const void *b) { return strcmp(((const Entry*)a)->p, ((const Entry*)b)->p); }

int main(void) {
    int N; if (scanf("%d", &N) != 1) return 1;
    char (*w)[12] = malloc((size_t)(N + 1) * 12);
    for (int i = 0; i < N; i++) scanf("%11s", w[i]);
    char A[12], B[12]; scanf("%11s %11s", A, B);
    int L = (int)strlen(A);
    int ia = -1, ib = -1;
    for (int i = 0; i < N; i++) { if (!strcmp(w[i], A)) ia = i; if (!strcmp(w[i], B)) ib = i; }
    if (ib == -1) { puts("-1"); return 0; }        /* B must be in D */
    if (!strcmp(A, B)) { puts("0"); return 0; }
    int M = N;
    if (ia == -1) { strcpy(w[M], A); ia = M++; }   /* A need not be in D */

    size_t T = (size_t)M * L;
    Entry *ent = malloc(T * sizeof(Entry));
    size_t k = 0;
    for (int i = 0; i < M; i++)
        for (int j = 0; j < L; j++, k++) {
            strcpy(ent[k].p, w[i]); ent[k].p[j] = '*'; ent[k].id = i; ent[k].pos = j;
        }
    qsort(ent, T, sizeof(Entry), cmp);

    int *gid = malloc(T * sizeof(int));            /* gid[word*L+pos] = group of that pattern */
    int *gstart = malloc((T + 1) * sizeof(int));
    int G = 0;
    for (size_t i = 0; i < T; i++) {
        if (i == 0 || strcmp(ent[i].p, ent[i - 1].p)) gstart[G++] = (int)i;
        gid[(size_t)ent[i].id * L + ent[i].pos] = G - 1;
    }
    gstart[G] = (int)T;

    int *dist[2], *fr[2], *nf = malloc(M * sizeof(int)); char *used[2];
    int fsz[2];
    for (int s = 0; s < 2; s++) {
        dist[s] = malloc(M * sizeof(int)); fr[s] = malloc(M * sizeof(int));
        used[s] = calloc(G, 1);
        for (int i = 0; i < M; i++) dist[s][i] = -1;
    }
    dist[0][ia] = 0; fr[0][0] = ia; fsz[0] = 1;    /* side 0: from A */
    dist[1][ib] = 0; fr[1][0] = ib; fsz[1] = 1;    /* side 1: from B */

    while (fsz[0] > 0 && fsz[1] > 0) {
        int s = fsz[0] <= fsz[1] ? 0 : 1, o = 1 - s;   /* expand the smaller frontier */
        int best = -1, cnt = 0;
        for (int f = 0; f < fsz[s]; f++) {
            int cur = fr[s][f];
            for (int j = 0; j < L; j++) {
                int g = gid[(size_t)cur * L + j];
                if (used[s][g]) continue;          /* each group scanned once per side */
                used[s][g] = 1;
                for (int t = gstart[g]; t < gstart[g + 1]; t++) {
                    int u = ent[t].id;
                    if (dist[o][u] != -1) {        /* frontiers meet */
                        int c = dist[s][cur] + 1 + dist[o][u];
                        if (best == -1 || c < best) best = c;
                    }
                    if (dist[s][u] == -1) { dist[s][u] = dist[s][cur] + 1; nf[cnt++] = u; }
                }
            }
        }
        if (best != -1) { printf("%d\n", best); return 0; }
        memcpy(fr[s], nf, cnt * sizeof(int)); fsz[s] = cnt;
    }
    puts("-1");
    return 0;
}
