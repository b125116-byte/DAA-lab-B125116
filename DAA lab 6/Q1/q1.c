
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int findMax(int a[], int n) {
    int max = a[0];
    for (int i = 1; i < n; i++)
        if (a[i] > max) max = a[i];
    return max;
}


void firstSecondLargest(int a[], int n, int *first, int *second) {
    if (a[0] > a[1]) { *first = a[0]; *second = a[1]; }
    else             { *first = a[1]; *second = a[0]; }
    for (int i = 2; i < n; i++) {
        if (a[i] > *first)       { *second = *first; *first = a[i]; }
        else if (a[i] > *second) { *second = a[i]; }
    }
}


double findMean(int a[], int n) {
    long long sum = 0;
    for (int i = 0; i < n; i++) sum += a[i];
    return (double)sum / n;
}

int cmpInt(const void *x, const void *y) { return (*(int *)x - *(int *)y); }


double findMedian(int a[], int n) {
    int *tmp = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) tmp[i] = a[i];
    qsort(tmp, n, sizeof(int), cmpInt);
    double median = (n % 2 == 0) ? (tmp[n/2 - 1] + tmp[n/2]) / 2.0 : tmp[n/2];
    free(tmp);
    return median;
}


double findStdDev(int a[], int n) {
    double mean = findMean(a, n);
    double sumSq = 0;
    for (int i = 0; i < n; i++) sumSq += (a[i] - mean) * (a[i] - mean);
    return sqrt(sumSq / n);
}


int findMode(int a[], int n) {
    int *tmp = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) tmp[i] = a[i];
    qsort(tmp, n, sizeof(int), cmpInt);
    int mode = tmp[0], modeCount = 1, curCount = 1;
    for (int i = 1; i < n; i++) {
        curCount = (tmp[i] == tmp[i-1]) ? curCount + 1 : 1;
        if (curCount > modeCount) { modeCount = curCount; mode = tmp[i]; }
    }
    free(tmp);
    return mode;
}


int removeDuplicates(int a[], int n) {
    if (n == 0) return 0;
    qsort(a, n, sizeof(int), cmpInt);
    int j = 0;
    for (int i = 1; i < n; i++)
        if (a[i] != a[j]) a[++j] = a[i];
    return j + 1;
}


void reverseArray(int a[], int n) {
    int i = 0, j = n - 1;
    while (i < j) { int t = a[i]; a[i] = a[j]; a[j] = t; i++; j--; }
}


int partitionGEFirst(int a[], int n) {
    int pivotIndex = rand() % n;
    int pivot = a[pivotIndex];
    int t = a[pivotIndex]; a[pivotIndex] = a[n-1]; a[n-1] = t; /* pivot to end */
    int store = 0;
    for (int i = 0; i < n - 1; i++) {
        if (a[i] >= pivot) { t = a[i]; a[i] = a[store]; a[store] = t; store++; }
    }
    t = a[store]; a[store] = a[n-1]; a[n-1] = t; /* pivot into place */
    return store;
}

void printArr(int a[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");
}

int main(void) {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    if (n < 2) { printf("Need at least 2 elements.\n"); return 1; }

    int *a = malloc(n * sizeof(int));
    printf("Enter %d integers: ", n);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);

    printf("\nArray: "); printArr(a, n);

    printf("(i)   Max                = %d\n", findMax(a, n));

    int first, second;
    firstSecondLargest(a, n, &first, &second);
    printf("(ii)  1st, 2nd largest   = %d, %d\n", first, second);

    printf("(iii) Mean               = %.4f\n", findMean(a, n));
    printf("(iv)  Median             = %.4f\n", findMedian(a, n));
    printf("(v)   Std deviation      = %.4f\n", findStdDev(a, n));
    printf("(vi)  Mode               = %d\n", findMode(a, n));

    int *b = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) b[i] = a[i];
    int newLen = removeDuplicates(b, n);
    printf("(vii) No duplicates      = "); printArr(b, newLen);

    int *c = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) c[i] = a[i];
    reverseArray(c, n);
    printf("(viii)Reversed           = "); printArr(c, n);

    srand(42);
    int *d = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) d[i] = a[i];
    int boundary = partitionGEFirst(d, n);
    printf("(ix)  Partitioned (>=pivot first) = "); printArr(d, n);
    printf("      boundary index = %d\n", boundary);

    free(a); free(b); free(c); free(d);
    return 0;
}
