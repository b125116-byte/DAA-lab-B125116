#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXS 100
#define LEN 1000

int overlap(const char *a, const char *b) {
    int la = (int)strlen(a);
    int lb = (int)strlen(b);

    for (int k = (la < lb ? la : lb); k > 0; k--) {
        if (strncmp(a + la - k, b, k) == 0)
            return k;
    }
    return 0;
}

int main(void) {
    char s[MAXS][LEN];
    int n;

    printf("Enter number of strings: ");
    scanf("%d", &n);
    if (n < 1 || n > MAXS) return 1;

    for (int i = 0; i < n; i++) {
        printf("Enter string %d: ", i + 1);
        scanf("%999s", s[i]);
    }

    // Remove strings already contained in another string.
    for (int i = 0; i < n; i++) {
        if (s[i][0] == '\0') continue;

        for (int j = 0; j < n; j++) {
            if (i != j && s[j][0] != '\0' &&
                strlen(s[i]) <= strlen(s[j]) &&
                strstr(s[j], s[i]) != NULL) {
                s[i][0] = '\0';
                break;
            }
        }
    }

    while (1) {
        int bi = -1, bj = -1, best = -1;

        for (int i = 0; i < n; i++) {
            if (s[i][0] == '\0') continue;

            for (int j = 0; j < n; j++) {
                if (i == j || s[j][0] == '\0') continue;

                int ov = overlap(s[i], s[j]);

                if (ov > best) {
                    best = ov;
                    bi = i;
                    bj = j;
                }
            }
        }

        if (bi == -1) break;

        // No positive overlap remains.
        if (best <= 0) {
            for (int i = 0; i < n; i++) {
                if (i != bi && s[i][0] != '\0') {
                    bi = i;
                    break;
                }
            }

            if (bi == bj || bj == -1) break;

            // This branch is handled by the positive-overlap
            // merge below only when an overlap exists.
            break;
        }

        int la = (int)strlen(s[bi]);
        int lb = (int)strlen(s[bj]);

        if (la + lb - best >= LEN) {
            printf("Merged string exceeds buffer size.\n");
            return 1;
        }

        strcat(s[bi], s[bj] + best);
        s[bj][0] = '\0';
    }

    // Concatenate remaining strings if no overlap is available.
    char answer[MAXS * LEN] = "";

    for (int i = 0; i < n; i++) {
        if (s[i][0] != '\0') {
            if (strlen(answer) + strlen(s[i]) >= sizeof(answer)) {
                printf("Result too large.\n");
                return 1;
            }
            strcat(answer, s[i]);
        }
    }

    printf("Greedy superstring: %s\n", answer);
    printf("Length: %lu\n", (unsigned long)strlen(answer));

    return 0;
}
