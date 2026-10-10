#include <stdio.h>
#include <limits.h>

#define MAX 200

long long w[MAX], prefix[MAX];
long long dp[MAX][MAX];
int split[MAX][MAX];

void printTree(int i, int j) {
    if (i == j) {
        printf("%d", i + 1);
        return;
    }

    printf("(");
    printTree(i, split[i][j]);
    printf(", ");
    printTree(split[i][j] + 1, j);
    printf(")");
}

int main(void) {
    int n;

    printf("Enter number of weights (1-%d): ", MAX);
    scanf("%d", &n);
    if (n < 1 || n > MAX) return 1;

    prefix[0] = 0;

    for (int i = 0; i < n; i++) {
        printf("Enter weight %d: ", i + 1);
        scanf("%lld", &w[i]);
        if (w[i] < 0) return 1;
        prefix[i + 1] = prefix[i] + w[i];
        dp[i][i] = 0;
    }

    for (int len = 2; len <= n; len++) {
        for (int i = 0; i + len <= n; i++) {
            int j = i + len - 1;
            long long sum = prefix[j + 1] - prefix[i];

            dp[i][j] = LLONG_MAX / 4;

            for (int r = i; r < j; r++) {
                long long cost = dp[i][r] + dp[r + 1][j] + sum;

                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                    split[i][j] = r;
                }
            }
        }
    }

    printf("Minimum weighted path length: %lld\n", dp[0][n - 1]);
    printf("Optimal alphabetic tree (leaf indices): ");
    printTree(0, n - 1);
    printf("\n");

    return 0;
}
