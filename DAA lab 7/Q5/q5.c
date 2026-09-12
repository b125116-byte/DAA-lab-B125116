#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Build the guaranteed-hit shot sequence; returns its length and fills shots[] */
int build_sequence(int n, int *shots) {
    if (n < 2) 
      return 0;
    if (n == 2) { shots[0] = 1; shots[1] = 1; 
                 return 2; }
    int k = 0;
    for (int s = 2; s <= n - 1; s++) shots[k++] = s;
    for (int s = n - 1; s >= 2; s--) shots[k++] = s;
    return k;
}

/* Simulate to verify the sequence guarantees a hit for every possible
   (unknown) starting position and every possible movement pattern */
int verify(int n, int *shots, int len) {
    int *possible = malloc(sizeof(int) * (n + 2));
    for (int i = 1; i <= n; i++) possible[i] = 1;   /* all positions possible */

    for (int t = 0; t < len; t++) {
        int s = shots[t];
        possible[s] = 0;                            /* shot there -> eliminated if present */
        int any = 0;
        for (int i = 1; i <= n; i++) if (possible[i]) { any = 1; break; }
        if (!any) { free(possible); 
                   return 1; }      
        int *nxt = calloc(n + 2, sizeof(int));
        for (int i = 1; i <= n; i++) {
            if (possible[i]) {
                if (i - 1 >= 1) nxt[i - 1] = 1;
                if (i + 1 <= n) nxt[i + 1] = 1;
            }
        }
        memcpy(possible, nxt, sizeof(int) * (n + 2));
        free(nxt);
    }
    int any = 0;
    for (int i = 1; i <= n; i++) if (possible[i]) any = 1;
    free(possible);
    return !any;
}

int main() {
    printf(" n | shot sequence guaranteeing a hit | #shots | verified?\n");
    printf("---+------------------------------------+--------+-----------\n");
    for (int n = 2; n <= 10; n++) {
        int shots[64];
        int len = build_sequence(n, shots);
        printf("%2d | ", n);
        for (int i = 0; i < len; i++) printf("%d ", shots[i]);
        printf("| %6d | %s\n", len, verify(n, shots, len) ? "YES" : "NO");
    }
    return 0;
}
