Find both smallest and largest elements with fewer comparisons than doing two separate scans.
Base case: for two elements, compare once. One becomes min and the other max.
Recursive case: split the array into two halves.
Recursively find (min, max) from each half.
Compare the two minimums, then compare the two maximums.

T(n)=2T(n/2)+2
For n a power of two, this uses:

(3n/2) - 2
comparisons, which satisfies the required bound of at most (3n/2).
