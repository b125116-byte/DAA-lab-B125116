#include <stdio.h>
#include <stdlib.h>

typedef struct { int r, c; } Coin;


int build_UT(int n, Coin *pts) {
    int k = 0;
    for (int r = 0; r < n; r++)
        for (int c = 0; c <= r; c++)
            pts[k].r = r, pts[k].c = c, k++;
    return k;
}


int build_DT(int n, Coin *pts) {
    int k = 0;
    for (int r = 0; r < n; r++)
        for (int c = r; c < n; c++)
            pts[k].r = r, pts[k].c = c, k++;
    return k;
}


int in_UT(int n, int r, int c) {
    return (r >= 0 && r < n && c >= 0 && c <= r);
}


int best_overlap(int n, int *best_a, int *best_b) {
    int N = n * (n + 1) / 2;
    Coin *DT = malloc(sizeof(Coin) * N);
    int m = build_DT(n, DT);

    int best = -1;
    for (int a = -n; a <= n; a++) {
        for (int b = -n; b <= n; b++) {
            int overlap = 0;
            for (int i = 0; i < m; i++)
                if (in_UT(n, DT[i].r + a, DT[i].c + b)) overlap++;
            if (overlap > best) { best = overlap; *best_a = a; *best_b = b; }
        }
    }
    free(DT);
    return best;
}

int main() {
    printf(" n | coins | min moves (search) | formula floor(n(n+1)/6) | best shift\n");
    printf("---+-------+---------------------+--------------------------+-----------\n");
    for (int n = 2; n <= 10; n++) {
        int N = n * (n + 1) / 2;
        int a, b;
        int overlap = best_overlap(n, &a, &b);
        int moves_search = N - overlap;
        int moves_formula = (n * (n + 1)) / 6;
        printf("%2d | %5d | %19d | %24d | (%d,%d)\n",
               n, N, moves_search, moves_formula, a, b);
    }

  
    int n = 4, a, b;
    best_overlap(n, &a, &b);
    printf("\nFor n = %d, the coins that MUST move (best shift a=%d,b=%d):\n", n, a, b);
    int N = n * (n + 1) / 2;
    Coin *DT = malloc(sizeof(Coin) * N);
    int m = build_DT(n, DT);
    for (int i = 0; i < m; i++) {
        if (!in_UT(n, DT[i].r + a, DT[i].c + b)) {
            printf("  target slot (row=%d,col=%d) needs a fresh coin\n", DT[i].r, DT[i].c);
        }
    }
    free(DT);
    return 0;
}
