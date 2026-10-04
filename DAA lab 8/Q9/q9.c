#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
typedef unsigned long long u64;

static int collatz_next(u64 n, u64 *out){           
    if (n % 2 == 0) { *out = n / 2; return 1; }
    if (n > (ULLONG_MAX - 1) / 3) return 0;
    *out = 3 * n + 1; return 1;
}
static int analyse(u64 n, int print, u64 *steps, u64 *peak){
    *steps = 0; *peak = n;
    if (print) printf("%llu", n);
    while (n != 1) {
        if (!collatz_next(n, &n)) { printf("\nOVERFLOW detected\n"); return 0; }
        (*steps)++; if (n > *peak) *peak = n;
        if (print) printf(" -> %llu", n);
    }
    if (print) printf("\n");
    return 1;
}
static void interval(u64 a, u64 b){
    unsigned *memo = calloc(b + 2, sizeof(unsigned));   /* memo[1]=0 */
    u64 bestN = 0; unsigned bestS = 0;
    for (u64 s = 2; s <= b; s++) {
        u64 n = s; unsigned k = 0;
        while (n >= s) {
            if (!collatz_next(n, &n)) { printf("Overflow at start %llu\n", s); free(memo); return; }
            k++;
        }
        memo[s] = k + memo[n];
        if (s >= a && memo[s] > bestS) { bestS = memo[s]; bestN = s; }
    }
    if (a <= 1 && bestS == 0) bestN = 1;
    u64 st, pk; analyse(bestN, 0, &st, &pk);
    printf("In [%llu,%llu]: longest trajectory starts at %llu (%u steps, peak %llu)\n", a, b, bestN, bestS, pk);
    free(memo);
}
int main(){
    int mode;
    if (scanf("%d", &mode) != 1) return 1;
    if (mode == 1) {
        u64 n, st, pk;
        scanf("%llu", &n);
        if (n < 1) { printf("n must be >= 1\n"); return 1; }
        if (analyse(n, 1, &st, &pk)) printf("Steps = %llu, Peak = %llu\n", st, pk);
    } else {
        u64 a, b; scanf("%llu %llu", &a, &b);
        if (a < 1 || a > b) { printf("Need 1 <= a <= b\n"); return 1; }
        interval(a, b);
    }
    return 0;
}
