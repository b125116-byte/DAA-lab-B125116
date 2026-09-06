#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long long reversalCount = 0;
long long totalCost = 0; /* sum of reversal lengths = the "cost" metric */


void reverseRange(int p[], int i, int j) {
    reversalCount++;
    totalCost += (j - i);
    j--;
    while (i < j) { int t = p[i]; p[i] = p[j]; p[j] = t; i++; j--; }
}


void pancakeSort(int p[], int n) {
    for (int size = n; size > 1; size--) {
        int maxIdx = 0;
        for (int i = 1; i < size; i++) if (p[i] > p[maxIdx]) maxIdx = i;
        if (maxIdx == size - 1) continue;                 /* already placed */
        if (maxIdx != 0) reverseRange(p, 0, maxIdx + 1);   /* bring max to front */
        reverseRange(p, 0, size);                          /* send it to the end */
    }
}


void rotateRange(int p[], int first, int middle, int last) {
    reverseRange(p, first, middle);
    reverseRange(p, middle, last);
    reverseRange(p, first, last);
}


int lowerBound(int p[], int lo, int hi, int key) {
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (p[mid] < key) lo = mid + 1; else hi = mid;
    }
    return lo;
}


int upperBound(int p[], int lo, int hi, int key) {
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (p[mid] <= key) lo = mid + 1; else hi = mid;
    }
    return lo;
}


void mergeNoBuffer(int p[], int first, int middle, int last) {
    int len1 = middle - first, len2 = last - middle;
    if (len1 == 0 || len2 == 0) return;
    if (len1 + len2 == 2) {
        if (p[middle] < p[first]) { int t = p[first]; p[first] = p[middle]; p[middle] = t; }
        return;
    }

    int first_cut, second_cut, len11, len22;
    if (len1 > len2) {
        first_cut = first + len1 / 2;
        second_cut = lowerBound(p, middle, last, p[first_cut]);
        len11 = len1 / 2;
        len22 = second_cut - middle;
    } else {
        second_cut = middle + len2 / 2;
        first_cut = upperBound(p, first, middle, p[second_cut]);
        len11 = first_cut - first;
        len22 = len2 / 2;
    }

    rotateRange(p, first_cut, middle, second_cut);
    int new_middle = first_cut + len22;
    mergeNoBuffer(p, first, first_cut, new_middle);
    mergeNoBuffer(p, new_middle, second_cut, last);
}


void mergeSortByReversal(int p[], int lo, int hi) {
    if (hi - lo <= 1) return;
    int mid = lo + (hi - lo) / 2;
    mergeSortByReversal(p, lo, mid);
    mergeSortByReversal(p, mid, hi);
    mergeNoBuffer(p, lo, mid, hi);
}

void printArr(int a[], int n) { for (int i = 0; i < n; i++) printf("%d ", a[i]); printf("\n"); }

int isSorted(int a[], int n) {
    for (int i = 1; i < n; i++) if (a[i - 1] > a[i]) return 0;
    return 1;
}

int main(void) {
    int n;
    printf("Enter n (permutation size): ");
    scanf("%d", &n);
    int *p1 = malloc(n * sizeof(int));
    int *p2 = malloc(n * sizeof(int));
    printf("Enter the permutation (1..n in any order): ");
    for (int i = 0; i < n; i++) { scanf("%d", &p1[i]); p2[i] = p1[i]; }

   
    reversalCount = 0; totalCost = 0;
    pancakeSort(p1, n);
    printf("\n[Part 1] Sorted via pancake-style reversals: ");
    printArr(p1, n);
    printf("[Part 1] Reversals used = %lld (O(n) bound: <= %d)\n", reversalCount, 2 * n - 2);
    printf("[Part 1] Sorted correctly? %s\n", isSorted(p1, n) ? "Yes" : "No");

    
    reversalCount = 0; totalCost = 0;
    mergeSortByReversal(p2, 0, n);
    printf("\n[Part 2] Sorted via reversal-based merge sort: ");
    printArr(p2, n);
    printf("[Part 2] Reversals used = %lld\n", reversalCount);
    double log2n = (n > 1) ? log2((double)n) : 1.0;
    printf("[Part 2] Total reversal cost (sum of lengths) = %lld ", totalCost);
    printf("(reference bound n*log2(n)^2 ~= %.1f)\n", n * log2n * log2n);
    printf("[Part 2] Sorted correctly? %s\n", isSorted(p2, n) ? "Yes" : "No");

    free(p1); free(p2);
    return 0;
}
