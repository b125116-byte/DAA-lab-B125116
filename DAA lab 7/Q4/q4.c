#include <stdio.h>

int sw[64];
int N;
long moveCount = 0;

void print_state() {
    printf("[");
    for (int i = 0; i < N; i++) printf("%d", sw[i]);
    printf("]\n");
}

void solve(int n);   /* solve and restore call each other */
void restore(int n);


void solve(int n) {
    if (n == 0) 
      return;
    solve(n - 1);
    sw[n - 1] ^= 1;               
    moveCount++;
    printf("Move %2ld: toggle switch %d  -> ", moveCount, n);
    print_state();
    restore(n - 1);
}


void restore(int n) {
    if (n == 0) return;
    solve(n - 1);
    sw[n - 1] ^= 1;
    moveCount++;
    printf("Move %2ld: toggle switch %d  -> ", moveCount, n);
    print_state();
    restore(n - 1);
}

int main() {
    N = 4;                        
    for (int i = 0; i < N; i++) sw[i] = 1;

    printf("Initial state (all ON): "); print_state();
    printf("\nSequence of moves to turn ALL switches OFF:\n");

    solve(N);

    printf("\nTotal moves used: %ld  (formula: 2^%d - 1 = %d)\n",
           moveCount, N, (1 << N) - 1);

    printf("\nMinimum-move table for various n:\n");
    printf(" n | min moves (2^n - 1)\n");
    for (int n = 1; n <= 10; n++)
        printf("%2d | %d\n", n, (1 << n) - 1);
    return 0;
}
