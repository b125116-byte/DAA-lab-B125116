#include <stdio.h>

#define MAX 100

typedef struct {
    int number;
    char colour; /* R, B, or Y */
} Item;

int main() {
    Item red[MAX], blue[MAX], yellow[MAX], x;
    int n, i, nr = 0, nb = 0, ny = 0;

    /* Input numbers must already be in increasing order. */
    printf("Enter n, then n lines: number colour (R/B/Y):\n");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        scanf("%d %c", &x.number, &x.colour);
        if (x.colour == 'R' || x.colour == 'r')
            red[nr++] = x;
        else if (x.colour == 'B' || x.colour == 'b')
            blue[nb++] = x;
        else
            yellow[ny++] = x;
    }

    /* Each list kept its original order, so this is stable. */
    printf("Result: ");
    for (i = 0; i < nr; i++) printf("(%d,R) ", red[i].number);
    for (i = 0; i < nb; i++) printf("(%d,B) ", blue[i].number);
    for (i = 0; i < ny; i++) printf("(%d,Y) ", yellow[i].number);
    printf("\n");
    return 0;
}
