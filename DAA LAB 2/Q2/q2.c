#include <stdio.h>
#include <stdlib.h>

// Global tracking metrics
long long counter_2way = 0;
long long counter_3way = 0;


// 1. STANDARD 2-WAY MERGE SORT IMPLEMENTATION

void merge2Way(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));
    
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
    
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        counter_2way++; // Track merge comparisons
        if (L[i] <= R[j]) { arr[k] = L[i]; i++; }
        else { arr[k] = R[j]; j++; }
        k++;
    }
    while (i < n1) { arr[k] = L[i]; i++; k++; }
    while (j < n2) { arr[k] = R[j]; j++; k++; }
    
    free(L); free(R);
}

void mergeSort2Way(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort2Way(arr, l, m);
        mergeSort2Way(arr, m + 1, r);
        merge2Way(arr, l, m, r);
    }
}


// 2. MODIFIED 3-WAY MERGE SORT IMPLEMENTATION

void merge3Way(int arr[], int low, int mid1, int mid2, int high) {
    int n1 = mid1 - low + 1;
    int n2 = mid2 - mid1;
    int n3 = high - mid2;
    
    int *L = malloc(n1 * sizeof(int));
    int *M = malloc(n2 * sizeof(int));
    int *R = malloc(n3 * sizeof(int));
    
    for (int i = 0; i < n1; i++) L[i] = arr[low + i];
    for (int i = 0; i < n2; i++) M[i] = arr[mid1 + 1 + i];
    for (int i = 0; i < n3; i++) R[i] = arr[mid2 + 1 + i];
    
    int i = 0, j = 0, k = 0, l = low;
    
    // Merge three parts together
    while ((i < n1) && (j < n2) && (k < n3)) {
        counter_3way++;
        if (L[i] <= M[j]) {
            counter_3way++;
            if (L[i] <= R[k]) { arr[l++] = L[i++]; }
            else { arr[l++] = R[k++]; }
        } else {
            counter_3way++;
            if (M[j] <= R[k]) { arr[l++] = M[j++]; }
            else { arr[l++] = R[k++]; }
        }
    }
    
    // Remaining pairs cleanup loops
    while ((i < n1) && (j < n2)) {
        counter_3way++;
        if (L[i] <= M[j]) { arr[l++] = L[i++]; }
        else { arr[l++] = M[j++]; }
    }
    while ((j < n2) && (k < n3)) {
        counter_3way++;
        if (M[j] <= R[k]) { arr[l++] = M[j++]; }
        else { arr[l++] = R[k++]; }
    }
    while ((i < n1) && (k < n3)) {
        counter_3way++;
        if (L[i] <= R[k]) { arr[l++] = L[i++]; }
        else { arr[l++] = R[k++]; }
    }
    
    while (i < n1) arr[l++] = L[i++];
    while (j < n2) arr[l++] = M[j++];
    while (k < n3) arr[l++] = R[k++];
    
    free(L); free(M); free(R);
}

void mergeSort3Way(int arr[], int low, int high) {
    if (low >= high) return;
    
    int mid1 = low + (high - low) / 3;
    int mid2 = low + 2 * (high - low) / 3;
    
    mergeSort3Way(arr, low, mid1);
    mergeSort3Way(arr, mid1 + 1, mid2);
    mergeSort3Way(arr, mid2 + 1, high);
    
    merge3Way(arr, low, mid1, mid2, high);
}


// 3. AUTOMATED GNUPLOT STREAM PIPE

void run_gnuplot_engine() {
    FILE *gnuPipe = popen("gnuplot", "w");
    if (!gnuPipe) {
        printf("[!] Gnuplot pipeline connection failed. Verification skipped.\n");
        return;
    }
    
    fprintf(gnuPipe, "set terminal pngcairo size 800,600 enhanced font 'Verdana,10'\n");
    fprintf(gnuPipe, "set output 'merge_sort_growth.png'\n");
    fprintf(gnuPipe, "set title 'Order of Growth: Standard vs. Modified 3-Way Merge Sort'\n");
    fprintf(gnuPipe, "set xlabel 'Array Capacity Size (N)'\n");
    fprintf(gnuPipe, "set ylabel 'Algorithmic Comparisons (Steps)'\n");
    fprintf(gnuPipe, "set grid\n");
    fprintf(gnuPipe, "set key left top\n");
    
    fprintf(gnuPipe, "plot 'merge_bench.dat' using 1:2 with linespoints title 'Standard 2-Way Merge Sort' lw 2 lc rgb 'blue', \\\n");
    fprintf(gnuPipe, "     'merge_bench.dat' using 1:3 with linespoints title 'Modified 3-Way Merge Sort' lw 2 lc rgb 'red'\n");
    
    pclose(gnuPipe);
    printf("[+] Analysis graphic completed and saved as: 'merge_sort_growth.png'\n");
}


// 4. MAIN BENCHMARK DRIVER ENGINE

int main() {
    FILE *df = fopen("merge_bench.dat", "w");
    if (!df) return 1;
    
    fprintf(df, "# N\tStandard2Way\tModified3Way\n");
    
    // Profile growing size vectors using worst-case reversed arrays
    for (int n = 10; n <= 1500; n += 50) {
        int *arr1 = malloc(n * sizeof(int));
        int *arr2 = malloc(n * sizeof(int));
        
        // Generate a reversed array to trigger worst-case comparison profiles
        for (int i = 0; i < n; i++) {
            arr1[i] = n - i;
            arr2[i] = n - i;
        }
        
        counter_2way = 0;
        counter_3way = 0;
        
        mergeSort2Way(arr1, 0, n - 1);
        mergeSort3Way(arr2, 0, n - 1);
        
        fprintf(df, "%d\t%lld\t%lld\n", n, counter_2way, counter_3way);
        
        free(arr1);
        free(arr2);
    }
    fclose(df);
    
    run_gnuplot_engine();
    return 0;
}
