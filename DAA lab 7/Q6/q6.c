#include <stdio.h>
#include <stdlib.h>

typedef struct { int year; int delta; } Event; /* delta = +1 birth, -1 (death+1) */

int cmp(const void *a, const void *b) {
    const Event *ea = a, *eb = b;
    if (ea->year != eb->year) return ea->year - eb->year;
    return ea->delta - eb->delta;   /* -1 (death) sorts before +1 (birth) on tie year */
}

int main() {
    /* sample "book index": name is implicit (index i), (birth, death) */
    int birth[] = {1564, 1643, 1571, 1630, 1473, 1608, 1642, 1452, 1596, 1666};
    int death[] = {1642, 1727, 1630, 1680, 1543, 1687, 1727, 1519, 1650, 1736};
    int n = sizeof(birth) / sizeof(birth[0]);

    Event *ev = malloc(sizeof(Event) * 2 * n);
    for (int i = 0; i < n; i++) {
        ev[2 * i]     = (Event){ birth[i],     +1 };
        ev[2 * i + 1] = (Event){ death[i] + 1, -1 };
    }
    qsort(ev, 2 * n, sizeof(Event), cmp);

    int alive = 0, best = -1, bestYear = -1;
    for (int i = 0; i < 2 * n; i++) {
        alive += ev[i].delta;
        if (alive > best) { best = alive; bestYear = ev[i].year; }
    }

    printf("Scientists (birth - death):\n");
    for (int i = 0; i < n; i++) printf("  #%2d : %d - %d\n", i + 1, birth[i], death[i]);

    printf("\nMaximum number of scientists alive simultaneously: %d\n", best);
    printf("This maximum is first reached starting in the year: %d\n", bestYear);

    free(ev);
    return 0;
}
