#include <stdio.h>
#include <stdlib.h>

int min_trials(int E, int F) {
    int *f = calloc(E + 1, sizeof(int));
    int t = 0;
    while (f[E] < F) {
        t++;
        for (int e = E; e >= 1; e--)
            f[e] = f[e] + f[e - 1] + 1; 
    }
    free(f);
    return t;
}

int main() {
    printf("E (eggs) | F (floors) | Min guaranteed trials\n");
    printf("---------+------------+-----------------------\n");
    int tests[][2] = { {1,100}, {2,100}, {2,36}, {3,100}, {4,1000}, {10,1000} };
    for (int i = 0; i < 6; i++) {
        int E = tests[i][0], F = tests[i][1];
        printf("%8d | %10d | %d\n", E, F, min_trials(E, F));
    }

   
    printf("\nClassic case: 2 eggs, 100-storey building -> %d trials\n",
           min_trials(2, 100));
    printf("(Check: with T trials and 2 eggs you can cover up to T(T+1)/2 floors;\n");
    printf(" 14*15/2 = 105 >= 100, 13*14/2 = 91 < 100, so 14 is optimal.)\n");
    return 0;
}
