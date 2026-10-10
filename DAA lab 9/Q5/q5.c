#include <stdio.h>

#define MAX 100000

int main() {
    int n, rating[MAX];
    long long candy[MAX], total = 0;

    printf("Enter number of children: ");
    scanf("%d", &n);
    if (n <= 0 || n > MAX) 
      return 1;

    printf("Enter ratings:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &rating[i]);
        candy[i] = 1;
    }

    for (int i = 1; i < n; i++) {
        if (rating[i] > rating[i - 1])
            candy[i] = candy[i - 1] + 1;
    }

    for (int i = n - 2; i >= 0; i--) {
        if (rating[i] > rating[i + 1] &&
            candy[i] <= candy[i + 1])
            candy[i] = candy[i + 1] + 1;
    }

    for (int i = 0; i < n; i++)
        total += candy[i];

    printf("Minimum candies required: %lld\n", total);
    return 0;
}
