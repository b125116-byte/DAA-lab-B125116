#include <stdio.h>
#include <stdlib.h>

#define MAX 100000

int cmp(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (x > y) - (x < y);
}

int main(void) {
    int n, start[MAX], end[MAX];

    printf("Enter number of meetings: ");
    scanf("%d", &n);
    if (n < 0 || n > MAX) return 1;

    for (int i = 0; i < n; i++) {
        printf("Enter start and end time: ");
        scanf("%d%d", &start[i], &end[i]);

        if (start[i] > end[i]) return 1;
    }

    if (n == 0) {
        printf("Minimum rooms required: 0\n");
        return 0;
    }

    qsort(start, n, sizeof(int), cmp);
    qsort(end, n, sizeof(int), cmp);

    int rooms = 0, maxRooms = 0, i = 0, j = 0;

    while (i < n) {
        if (start[i] < end[j]) {
            rooms++;
            if (rooms > maxRooms) maxRooms = rooms;
            i++;
        } else {
            rooms--;
            j++;
        }
    }

    printf("Minimum rooms required: %d\n", maxRooms);
    return 0;
}
