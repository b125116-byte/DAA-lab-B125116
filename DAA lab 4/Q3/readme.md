You have a set of integers, a number k, and target T. Check whether exactly k different numbers add up to T.
Example:
S = {1, 3, 4, 6, 8, 10}
k = 3
T = 15

A valid answer is:
1 + 4 + 10 = 15

Simple approach:
Sort the set.
Try choosing the first k - 1 numbers.
After choosing them, calculate the final number needed.
Binary-search for that final number.

The required complexity is O(n^(k-1) log n) because there can be up to n^(k-1) choices for the first k - 1 values, and each final check uses binary search.
