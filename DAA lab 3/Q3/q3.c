#include <stdio.h>

long long comparisons = 0;

void maxMin(int arr[], int low, int high, int *max, int *min) {
    if (low == high) {                 /* one element: no comparison needed */
        *max = *min = arr[low];
        return;
    }
    if (high == low + 1) {             /* two elements: 1 comparison */
        comparisons++;
        if (arr[low] > arr[high]) { *max = arr[low]; *min = arr[high]; }
        else { *max = arr[high]; *min = arr[low]; }
        return;
    }

    int mid = (low + high) / 2;
    int lmax, lmin, rmax, rmin;
    maxMin(arr, low, mid, &lmax, &lmin);
    maxMin(arr, mid + 1, high, &rmax, &rmin);

    comparisons += 2;                  /* combine step: 2 comparisons */
    *max = (lmax > rmax) ? lmax : rmax;
    *min = (lmin < rmin) ? lmin : rmin;
}

int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

    int maxVal, minVal;
    comparisons = 0;
    maxMin(arr, 0, n - 1, &maxVal, &minVal);

    printf("\nMaximum = %d\n", maxVal);
    printf("Minimum = %d\n", minVal);
    printf("Comparisons used = %lld\n", comparisons);
    printf("Bound 3n/2 = %.1f  (comparisons should never exceed this;\n", 1.5 * n);
    printf("the exact worst case 3n/2 - 2 is achieved when n is a power of 2)\n");

    return 0;
}
