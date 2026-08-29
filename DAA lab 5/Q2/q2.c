#include <stdio.h>
#include <stdlib.h>

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            int temp = arr[i]; 
            arr[i] = arr[j]; 
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1]; 
    arr[i + 1] = arr[high]; 
    arr[high] = temp;
    return i + 1;
}

int kthSmallest(int arr[], int low, int high, int k) {
    if (low == high) return arr[low];

    int pivotIndex = partition(arr, low, high);
    int rank = pivotIndex - low + 1;

    if (rank == k)
        return arr[pivotIndex];
    else if (k < rank)
        return kthSmallest(arr, low, pivotIndex - 1, k);
    else
        return kthSmallest(arr, pivotIndex + 1, high, k - rank);
}

int main() {
    int n, k;
    printf("Enter number of elements N: ");
    scanf("%d", &n);

    int *arr = malloc(n * sizeof(int));
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

    printf("Enter K (1 to %d): ", n);
    scanf("%d", &k);

    if (k < 1 || k > n) {
        printf("Invalid value of K\n");
    } else {
        int result = kthSmallest(arr, 0, n - 1, k);
        printf("The %d-th smallest element is %d\n", k, result);
    }

    free(arr);
    return 0;
}
