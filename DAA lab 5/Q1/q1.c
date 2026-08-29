#include <stdio.h>
#include <stdlib.h>

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            int temp = arr[i]; arr[i] = arr[j]; arr[j] = temp;
        }
    }
    int temp = arr[i + 1]; arr[i + 1] = arr[high]; arr[high] = temp;
    return i + 1;
}


int quickSelect(int arr[], int low, int high, int k) {
    if (low == high) return arr[low];

    int pivotIndex = partition(arr, low, high);
    int rank = pivotIndex - low + 1;  

    if (rank == k)
        return arr[pivotIndex];
    else if (k < rank)
        return quickSelect(arr, low, pivotIndex - 1, k);
    else
        return quickSelect(arr, pivotIndex + 1, high, k - rank);
}

double findMedian(int original[], int n) {
    int *arr = malloc(n * sizeof(int));

    if (n % 2 == 1) {
        for (int i = 0; i < n; i++) arr[i] = original[i];
        int mid = quickSelect(arr, 0, n - 1, (n + 1) / 2);
        free(arr);
        return (double) mid;
    } else {
        for (int i = 0; i < n; i++) arr[i] = original[i];
        int a = quickSelect(arr, 0, n - 1, n / 2);

       
        for (int i = 0; i < n; i++) arr[i] = original[i];
        int b = quickSelect(arr, 0, n - 1, n / 2 + 1);

        free(arr);
        return (a + b) / 2.0;
    }
}

int main() {
    int n;
    printf("Enter number of elements N: ");
    scanf("%d", &n);

    int *arr = malloc(n * sizeof(int));
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

    double median = findMedian(arr, n);
    printf("Median = %.2f\n", median);

    free(arr);
    return 0;
}
