#include <stdio.h>

int weighCount = 0;

/* Simulated balance scale: weighs coins in [l1..r1] against coins in [l2..r2].
   Returns -1 if left pan is lighter, 1 if right pan is lighter, 0 if balanced. */

int weighRanges(double w[], int l1, int r1, int l2, int r2) {
    weighCount++;
    double s1 = 0, s2 = 0;
    for (int i = l1; i <= r1; i++) s1 += w[i];
    for (int i = l2; i <= r2; i++) s2 += w[i];
    if (s1 < s2) return -1;
    if (s1 > s2) return 1;
    return 0;
}

/* Compares a single suspect coin against one known-genuine coin. */

int compareToGood(double w[], int idx, int ref) {
    weighCount++;
    return (w[idx] < w[ref]) ? -1 : 0;     /* -1 = idx is lighter (defective) */
}

/* Finds the defective (lighter) coin in w[low..high], or returns -1 if none.
   knownGood = index of a coin already proven genuine (-1 if none known yet). */

int findDefective(double w[], int low, int high, int knownGood) {
    int m = high - low + 1;
    if (m <= 0) return -1;

    if (m == 1) {
        if (knownGood == -1) return low;                                /* only suspect left, arrived here via a lighter pan */
        return (compareToGood(w, low, knownGood) == -1) ? low : -1;
    }

    int half = m / 2;
    int mid = low + half - 1;                       /* left half  = [low, mid]      */
    int rStart = mid + 1, rEnd = mid + half;        /* right half = [rStart, rEnd] */
    int leftover = (m - 2 * half == 1) ? high : -1; /* set-aside coin if m is odd */

    int cmp = weighRanges(w, low, mid, rStart, rEnd);

    if (cmp == -1) 
      return findDefective(w, low, mid, knownGood);      /* left pan lighter  */
    if (cmp == 1)  
      return findDefective(w, rStart, rEnd, knownGood);  /* right pan lighter */

    /* balanced -> every coin in [low..high] except possibly the leftover is genuine */
  
    int good = low;
    if (leftover != -1) 
      return findDefective(w, leftover, leftover, good);
    return -1;
}

int main() {
    int n;
    printf("Enter number of coins: ");
    scanf("%d", &n);
    double w[n];
    printf("Enter %d coin weights (e.g. all 10.0, and 9.0 for the one lighter coin, if any):\n", n);
    for (int i = 0; i < n; i++) 
      scanf("%lf", &w[i]);

    weighCount = 0;
    int res = findDefective(w, 0, n - 1, -1);

    if (res == -1)
        printf("\nNo defective coin found. All %d coins are genuine.\n", n);
    else
        printf("\nDefective (lighter) coin found at index %d (weight = %.2f)\n", res, w[res]);

    printf("Number of weighings used: %d  (bound: floor(log2(n)) + c)\n", weighCount);
    return 0;
}
