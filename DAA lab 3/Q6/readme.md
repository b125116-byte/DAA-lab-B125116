 Loop invariant (for the outer loop, index i):
    At the start of each iteration, the subarray A[0..i-1] contains the
    i smallest elements of the original array, in sorted (non-decreasing) order.
 
  Initialization: before the first iteration, i = 0, so A[0..i-1] is empty,
    which is trivially "sorted and contains the 0 smallest elements."
 
  Maintenance: each iteration finds the minimum of A[i..n-1] and swaps it
    into A[i]. This extends the sorted prefix to A[0..i], which still holds
    the i+1 smallest elements in sorted order, so the invariant holds for i+1.
 
  Termination: the loop stops when i = n-1. By the invariant, A[0..n-2]
    contains the n-1 smallest elements in sorted order, and since A[n-1] is
    necessarily the single largest remaining element, the whole array A[0..n-1]
    is sorted. The loop only needs to run for the first (n-1) elements because
    once the first n-1 positions hold the n-1 smallest elements in order, the
    last element is forced to be the maximum and is already in place -- one
    more "find and swap" pass on a single-element range would do nothing.
 
  Running time:
    Worst case:  Theta(n^2)  (the inner loop always scans the remaining elements)
    Best case:   also Theta(n^2) -- unlike insertion sort, selection sort always
                 scans A[i+1..n-1] to find the minimum, regardless of the input
                 order, so there is no better best case.
