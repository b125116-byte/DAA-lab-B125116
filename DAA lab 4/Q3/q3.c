#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int compare(const void *a, const void *b) {
    int x = *(const int *)a, y = *(const int *)b;
    return (x > y) - (x < y);
}

int binary_search(int a[], int n, int target) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (a[mid] == target) return 1;
        if (a[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return 0;
}

/* Select k-1 increasing positions; binary-search for the last value. */
int k_sum(int s[], int n, int k, int start, int sum, int target) {
    int i;
    if (k == 1)
        return binary_search(s + start, n - start, target - sum);

    for (i = start; i <= n - k; i++)
        if (k_sum(s, n, k - 1, i + 1, sum + s[i], target))
            return 1;
    return 0;
}

int main() {
    int s[MAX], n, k, target, i;
    printf("Enter n, set elements, k, then target T:\n");
    scanf("%d", &n);
    for (i = 0; i < n; i++) scanf("%d", &s[i]);
    scanf("%d %d", &k, &target);

    if (k < 1 || k > n) {
        printf("k must be between 1 and n.\n");
        return 0;
    }
    qsort(s, n, sizeof(s[0]), compare);
    printf(k_sum(s, n, k, 0, 0, target) ?
           "Yes, a k-sum exists.\n" : "No k-sum exists.\n");
    return 0;
}
