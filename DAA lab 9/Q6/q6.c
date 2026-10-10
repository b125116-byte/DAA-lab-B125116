#include <stdio.h>
#include <string.h>

#define MAX 10000
#define ASCII 256

int main() {
    char s[MAX + 1], ans[MAX + 1];
    int freq[ASCII] = {0};
    int n, k, last[ASCII];

    printf("Enter string (no spaces): ");
    scanf("%10000s", s);

    printf("Enter minimum distance K: ");
    scanf("%d", &k);

    n = (int)strlen(s);
    for (int i = 0; i < ASCII; i++) last[i] = -MAX;

    for (int i = 0; i < n; i++)
        freq[(unsigned char)s[i]]++;

    for (int pos = 0; pos < n; pos++) {
        int best = -1;

        for (int c = 0; c < ASCII; c++) {
            if (freq[c] == 0) continue;
            if (pos - last[c] < k) continue;

            if (best == -1 || freq[c] > freq[best])
                best = c;
        }

        if (best == -1) {
            printf("Impossible: empty string returned.\n");
            return 0;
        }

        ans[pos] = (char)best;
        freq[best]--;
        last[best] = pos;
    }

    ans[n] = '\0';
    printf("Reorganized string: %s\n", ans);
    return 0;
}
