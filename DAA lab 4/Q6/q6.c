#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int point;
    int change; /* left endpoint = +1; right endpoint = -1 */
} Event;

int compare(const void *a, const void *b) {
    const Event *x = a, *y = b;
    if (x->point != y->point)
        return (x->point > y->point) - (x->point < y->point);
    return y->change - x->change; /* +1 before -1 at the same endpoint */
}

int main() {
    Event e[2 * MAX];
    int n, i, current = 0, maximum = 0, best_point = 0;
    printf("Enter n, then n lines: left right:\n");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        scanf("%d %d", &e[2*i].point, &e[2*i + 1].point);
        e[2*i].change = 1;
        e[2*i + 1].change = -1;
    }

    qsort(e, 2 * n, sizeof(e[0]), compare);
    for (i = 0; i < 2 * n; i++) {
        current += e[i].change;
        if (current > maximum) {
            maximum = current;
            best_point = e[i].point;
        }
    }
    printf("A best point is %d; it is in %d intervals.\n",
           best_point, maximum);
    return 0;
}

