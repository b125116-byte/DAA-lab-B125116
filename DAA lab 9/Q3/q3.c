#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

typedef struct {
    int d, fuel;
} Station;

int cmp(const void *a, const void *b) {
    Station *x = (Station *)a, *y = (Station *)b;
    return (x->d > y->d) - (x->d < y->d);
}

void push(int h[], int *n, int x) {
    int i = ++(*n);
    while (i > 1 && h[i / 2] < x) {
        h[i] = h[i / 2];
        i /= 2;
    }
    h[i] = x;
}

int pop(int h[], int *n) {
    int result = h[1], x = h[(*n)--], i = 1;
    while (2 * i <= *n) {
        int c = 2 * i;
        if (c < *n && h[c + 1] > h[c]) c++;
        if (h[c] <= x) break;
        h[i] = h[c];
        i = c;
    }
    if (*n > 0) h[i] = x;
    return result;
}

int main() {
    Station a[MAX];
    int n, D, F, h[MAX + 1], size = 0, stops = 0;

    printf("Enter target distance, initial fuel, number of stations: ");
    scanf("%d%d%d", &D, &F, &n);
    if (n < 0 || n >= MAX || D < 0 || F < 0) 
      return 1;

    for (int i = 0; i < n; i++) {
        printf("Enter station distance and fuel: ");
        scanf("%d%d", &a[i].d, &a[i].fuel);
    }

    qsort(a, n, sizeof(Station), cmp);

    long long reach = F;
    int i = 0;

    while (reach < D) {
        while (i < n && a[i].d <= reach)
            push(h, &size, a[i++].fuel);

        if (size == 0) {
            printf("Destination cannot be reached.\n");
            return 0;
        }

        reach += pop(h, &size);
        stops++;
    }

    printf("Minimum refuelling stops: %d\n", stops);
    return 0;
}
