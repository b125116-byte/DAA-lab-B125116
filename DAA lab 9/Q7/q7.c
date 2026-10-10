#include <stdio.h>

#define MAX 100000

int main(void) {
    int n, a[MAX];
    int minVal = 0, maxVal = 0;
    long long best;

    printf("Enter array size: ");
    scanf("%d", &n);
    if (n <= 0 || n > MAX) return 1;

    printf("Enter positive integers:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        if (a[i] <= 0 || a[i] > 1000000000) return 1;

        if (a[i] % 2 == 1)
            a[i] *= 2;
    }

    minVal = a[0];
    maxVal = a[0];

    for (int i = 1; i < n; i++) {
        if (a[i] < minVal) minVal = a[i];
        if (a[i] > maxVal) maxVal = a[i];
    }

    best = (long long)maxVal - minVal;

    while (maxVal % 2 == 0) {
        int idx = 0;

        for (int i = 1; i < n; i++)
            if (a[i] > a[idx])
                idx = i;

        maxVal = a[idx] / 2;
        a[idx] = maxVal;

        if (maxVal < minVal)
            minVal = maxVal;

        long long deviation = (long long)maxVal - minVal;
        if (deviation < best)
            best = deviation;

        maxVal = a[0];
        for (int i = 1; i < n; i++)
            if (a[i] > maxVal)
                maxVal = a[i];
    }

    printf("Minimum deviation: %lld\n", best);
    return 0;
}
