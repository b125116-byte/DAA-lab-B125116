#include <stdio.h>
#include <math.h>

long long binCount = 0, terCount = 0;

int binarySearch(int arr[], int low, int high, int x) {
    while (low <= high) {
        int mid = low + (high - low) / 2;
        binCount++;
        if (arr[mid] == x) 
          return mid;
        else if (arr[mid] < x) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

int ternarySearch(int arr[], int low, int high, int x) {
    while (low <= high) {
        int mid1 = low + (high - low) / 3;
        int mid2 = high - (high - low) / 3;

        terCount++;
        if (arr[mid1] == x) 
          return mid1;
        terCount++;
        if (arr[mid2] == x) 
          return mid2;

        if (x < arr[mid1]) high = mid1 - 1;
        else if (x > arr[mid2]) low = mid2 + 1;
        else { low = mid1 + 1; high = mid2 - 1; }
    }
    return -1;
}

int main() {
    int n;
    printf("Enter size of sorted array: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter %d sorted elements:\n", n);
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

    int x;
    printf("Enter element to search: ");
    scanf("%d", &x);

    binCount = 0; terCount = 0;
    int bIdx = binarySearch(arr, 0, n - 1, x);
    int tIdx = ternarySearch(arr, 0, n - 1, x);

    printf("\nBinary Search : %s at index %d, comparisons used = %lld\n",
           bIdx != -1 ? "found" : "not found", bIdx, binCount);
    printf("Ternary Search: %s at index %d, comparisons used = %lld\n",
           tIdx != -1 ? "found" : "not found", tIdx, terCount);

    double logBase2 = log2((double)n);
    double logBase3 = log((double)n) / log(3.0);
    printf("\nTheoretical worst case:\n");
    printf("  Binary  ~ log2(n)   = %.2f recursive steps (1 comparison each)\n", logBase2);
    printf("  Ternary ~ log3(n)   = %.2f recursive steps (up to 2 comparisons each)\n", logBase3);
    printf("  => Binary needs about %.2f comparisons, Ternary needs about %.2f comparisons\n",
           logBase2, 2 * logBase3);
    printf("This shows binary search's per-level cost (1 comparison) beats ternary's\n");
    printf("per-level cost (2 comparisons) even though ternary shrinks the range faster,\n");
    printf("because 2*log3(n) > log2(n) for all n > 1 (log2(3) < 2).\n");

    return 0;
}
