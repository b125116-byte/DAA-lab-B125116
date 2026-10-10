#include <stdio.h>

#define MAX 1000

long long h[MAX + 1];
int size = 0;

void push(long long x) {
    int i = ++size;
    while (i > 1 && h[i / 2] > x) {
        h[i] = h[i / 2];
        i /= 2;
    }
    h[i] = x;
}

long long pop(void) {
    long long ans = h[1], x = h[size--];
    int i = 1;
    while (2 * i <= size) {
        int c = 2 * i;
        if (c < size && h[c + 1] < h[c]) c++;
        if (h[c] >= x) break;
        h[i] = h[c];
        i = c;
    }
    if (size > 0) h[i] = x;
    return ans;
}

int main() {
    int n;
    long long cost = 0;

    printf("Enter number of sticks: ");
    scanf("%d", &n);
    if (n < 1 || n > MAX) return 1;

    for (int i = 0; i < n; i++) {
        long long x;
        scanf("%lld", &x);
        if (x < 0) return 1;
        push(x);
    }

    while (size > 1) {
        long long x = pop();
        long long y = pop();
        long long sum = x + y;
        cost += sum;
        push(sum);
    }

    printf("Minimum total cost: %lld\n", cost);
    return 0;
}
