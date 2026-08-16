Implement both searches on a sorted array.

Binary search divides the range into 2 parts, checks the middle element, then continues in one half.

Ternary search divides it into 3 parts, checks two dividing positions, then continues in one third.
Both take logarithmic time:
Binary = O(log2n), 
Ternary = O(log3n)
Although ternary search has fewer levels, it needs more comparisons per level (usually two pivots). 
Therefore binary search is generally faster in practice.
