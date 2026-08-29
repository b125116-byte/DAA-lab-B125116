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

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i]; arr[i] = arr[j]; arr[j] = temp;
        }
    }
    int temp = arr[i + 1]; arr[i + 1] = arr[high]; arr[high] = temp;
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    int n;
    printf("Enter number of random elements N to generate: ");
    scanf("%d", &n);

    generateFile("input.txt", n);
    printf("Generated %d random numbers in input.txt\n", n);

    int *arr = readFile("input.txt", n);

    quickSort(arr, 0, n - 1);

    writeFile("sorted_output.txt", arr, n);
    printf("Sorted data written to sorted_output.txt\n");

    free(arr);
    return 0;
}
