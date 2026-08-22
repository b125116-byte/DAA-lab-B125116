#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int left, right;
} Interval;

int compare(const void *a, const void *b) {
    const Interval *x = a, *y = b;
    return (x->left > y->left) - (x->left < y->left);
}

int main(void) {
    Interval a[MAX], current;
    int n, i;
    printf("Enter n, then n lines: left right:\n");
    scanf("%d", &n);
    if (n <= 0) return 0;

    for (i = 0; i < n; i++) scanf("%d %d", &a[i].left, &a[i].right);
    qsort(a, n, sizeof(a[0]), compare);

    current = a[0];
    printf("Merged intervals: ");
    for (i = 1; i < n; i++) {
        if (a[i].left <= current.right) { /* overlap */
            if (a[i].right > current.right) current.right = a[i].right;
        } else {
            printf("(%d,%d) ", current.left, current.right);
            current = a[i];
        }
    }
    printf("(%d,%d)\n", current.left, current.right);
    return 0;
}
