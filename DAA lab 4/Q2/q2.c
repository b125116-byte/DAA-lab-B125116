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
        if (a[mid] == target) 
          return 1;
        if (a[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return 0;
}

int main() {
    int s1[MAX], s2[MAX], n, x, i;
    printf("Enter n, S1, S2, then target x:\n");
    scanf("%d", &n);
    for (i = 0; i < n; i++) scanf("%d", &s1[i]);
    for (i = 0; i < n; i++) scanf("%d", &s2[i]);
    scanf("%d", &x);

    qsort(s2, n, sizeof(s2[0]), compare);
    for (i = 0; i < n; i++) {
        int needed = x - s1[i];
        if (binary_search(s2, n, needed)) {
            printf("Yes: %d + %d = %d\n", s1[i], needed, x);
            return 0;
        }
    }
    printf("No such pair exists.\n");
    return 0;
}
}
