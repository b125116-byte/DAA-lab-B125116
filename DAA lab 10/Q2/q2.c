#include <stdio.h>
#include <stdlib.h>

int *parent, *rnk;

int find(int x) {
    while (parent[x] != x) {
        parent[x] = parent[parent[x]];   
        x = parent[x];
    }
    return x;
}

int unite(int a, int b) {               
    a = find(a); b = find(b);
    if (a == b) 
      return 0;
    if (rnk[a] < rnk[b]) { int t = a; a = b; b = t; }
    parent[b] = a;
    if (rnk[a] == rnk[b]) rnk[a]++;
    return 1;
}

int main(void) {
    int R, C, K;
    scanf("%d %d %d", &R, &C, &K);
    int N = R * C;
    parent = malloc(N * sizeof(int));
    rnk    = calloc(N, sizeof(int));
    char *land = calloc(N, 1);
    for (int i = 0; i < N; i++) parent[i] = i;

    int dr[4] = {-1, 1, 0, 0}, dc[4] = {0, 0, -1, 1};
    int count = 0;
    for (int i = 0; i < K; i++) {
        int r, c;
        scanf("%d %d", &r, &c);
        int id = r * C + c;                       
        if (!land[id]) {
            land[id] = 1;
            count++;                              
            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d], nc = c + dc[d];
                if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
                int nid = nr * C + nc;
                if (land[nid] && unite(id, nid)) count--;   
            }
        }
        printf("%d ", count);
    }
    printf("\n");
    free(parent); 
  free(rnk); 
  free(land);
    return 0;
}
