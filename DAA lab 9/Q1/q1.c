#include <stdio.h>

#define MAX 100

typedef struct {
    double value, weight, decay, density;
} Item;

int main() {
    Item a[MAX], temp;
    int n;
    double W, total = 0, time = 0;

    printf("Enter number of items: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX) {
        printf("Invalid number of items.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("Enter value, weight and decay rate: ");
        scanf("%lf %lf %lf",
              &a[i].value, &a[i].weight, &a[i].decay);

        if (a[i].weight <= 0 || a[i].decay < 0) {
            printf("Invalid item data.\n");
            return 1;
        }

        a[i].density = a[i].value / a[i].weight;
    }

    printf("Enter knapsack capacity: ");
    scanf("%lf", &W);

  
    for (int i = 0; i < n; i++) {
        int best = i;

        for (int j = i + 1; j < n; j++) {
            double di = a[best].density - a[best].decay * time;
            double dj = a[j].density - a[j].decay * time;
            if (dj > di)
                best = j;
        }

        temp = a[i];
        a[i] = a[best];
        a[best] = temp;

        if (W <= 0)
            break;

        double fraction = W < a[i].weight
                            ? W / a[i].weight : 1.0;
        double effective = a[i].density - a[i].decay * time;

        if (effective > 0) {
            total += fraction * a[i].weight * effective;
            W -= fraction * a[i].weight;
        }

        printf("Item %d: fraction = %.2f\n", i + 1, fraction);
        time += 1.0;
    }

    printf("Total value: %.2f\n", total);
    return 0;
}
