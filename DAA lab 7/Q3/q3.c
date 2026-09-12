#include <stdio.h>
#include <stdlib.h>

long moveCount = 0;


void hanoi3(int n, int a, int b, int c, int print) {
    if (n == 0) return;
    hanoi3(n - 1, a, c, b, print);
    moveCount++;
    if (print) printf("  Move disk %d from peg %d to peg %d\n", n, a, c);
    hanoi3(n - 1, b, a, c, print);
}

long best_k[1000];       


long *build_frame_stewart(int N) {
    long *f = malloc(sizeof(long) * (N + 1));
    f[0] = 0;
    for (int n = 1; n <= N; n++) {
        long best = -1, bk = 0;
        for (int k = 0; k < n; k++) {
            long cand = 2 * f[k] + ((1L << (n - k)) - 1);
            if (best == -1 || cand < best) { best = cand; bk = k; }
        }
        f[n] = best;
        best_k[n] = bk;
    }
    return f;
}


void hanoi4(int n, int a, int b, int c, int d, long *f, int print) {
    if (n == 0) 
      return;
    if (n == 1) { moveCount++; if (print) printf("  Move disk 1 from peg %d to peg %d\n", a, c); 
                 return; }
    int k = best_k[n];
    hanoi4(k, a, b, d, c, f, print);          /* k disks: a -> b, spare d, using all 4 pegs */
    hanoi3(n - k, a, d, c, print);            /* n-k largest disks: a -> c using 3 pegs (b holds small disks) */
    hanoi4(k, b, a, c, d, f, print);          /* k disks: b -> c, spare a, using all 4 pegs */
}

int main() {
    int N = 15;
    long *f = build_frame_stewart(N);

    printf("n (disks) | min moves with 4 pegs (Frame-Stewart)\n");
    printf("----------+----------------------------------------\n");
    for (int n = 1; n <= N; n++) printf("%9d | %ld\n", n, f[n]);

    printf("\n--- Solving the classic 8-disk Reve's puzzle (expect 33 moves) ---\n");
    moveCount = 0;
    hanoi4(8, 0, 1, 2, 3, f, 1);
    printf("Total moves used: %ld\n", moveCount);

    free(f);
    return 0;
}
