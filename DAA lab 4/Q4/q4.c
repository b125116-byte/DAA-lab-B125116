#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int time;
    int change; /* entry = +1, exit = -1 */
} Event;

int compare(const void *a, const void *b) {
    const Event *x = a, *y = b;
    return (x->time > y->time) - (x->time < y->time);
}

int main() {
    Event e[2 * MAX];
    int n, i, current = 0, maximum = 0, best_time = -1;
    printf("Enter n, then n lines: entry_time exit_time:\n");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        scanf("%d %d", &e[2*i].time, &e[2*i + 1].time);
        e[2*i].change = 1;
        e[2*i + 1].change = -1;
    }

    qsort(e, 2 * n, sizeof(e[0]), compare);
    for (i = 0; i < 2 * n; i++) {
        current += e[i].change;
        if (current > maximum) {
            maximum = current;
            best_time = e[i].time;
        }
    }
    printf("Maximum people = %d, first reached at time %d\n",
           maximum, best_time);
    return 0;
}
}
