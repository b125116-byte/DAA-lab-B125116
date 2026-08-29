#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generateFile(const char *filename, int n) {
    FILE *fp = fopen(filename, "w");
    if (!fp) { printf("Error opening file for writing\n"); exit(1); }
    srand((unsigned) time(NULL));
    for (int i = 0; i < n; i++)
        fprintf(fp, "%d\n", rand() % 10000);
    fclose(fp);
}

int *readFile(const char *filename, int n) {
    FILE *fp = fopen(filename, "r");
    if (!fp) { printf("Error opening file for reading\n"); exit(1); }
    int *arr = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        fscanf(fp, "%d", &arr[i]);
    fclose(fp);
    return arr;
}

void writeFile(const char *filename, int arr[], int n) {
    FILE *fp = fopen(filename, "w");
    if (!fp) { printf("Error opening file for writing\n"); exit(1); }
    for (int i = 0; i < n; i++)
        fprintf(fp, "%d\n", arr[i]);
    fclose(fp);
}

/* Sift the element at index i down to maintain the max-heap property,
   within a heap of size n */
void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;

    if (largest != i) {
        int temp = arr[i]; arr[i] = arr[largest]; arr[largest] = temp;
        heapify(arr, n, largest);   /* keep sifting down */
    }
}

void heapSort(int arr[], int n) {
    /* Step 1: Build a max-heap out of the array */
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    /* Step 2: Repeatedly move the current max (root) to the end */
    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0]; arr[0] = arr[i]; arr[i] = temp;
        heapify(arr, i, 0);   /* re-heapify the reduced heap */
    }
}

int main() {
    int n;
    printf("Enter number of random elements N to generate: ");
    scanf("%d", &n);

    generateFile("input2.txt", n);
    printf("Generated %d random numbers in input2.txt\n", n);

    int *arr = readFile("input2.txt", n);

    heapSort(arr, n);

    writeFile("heap_sorted_output.txt", arr, n);
    printf("Sorted data written to heap_sorted_output.txt\n");

    free(arr);
    return 0;
}
