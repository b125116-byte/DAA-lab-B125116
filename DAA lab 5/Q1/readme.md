
 The question tells us to find the median of a list of N numbers WITHOUT sorting the list.
 
  Idea: Use QuickSelect (a variant of QuickSort's partitioning) to
  directly find the element(s) at the median rank, without sorting
  the entire array.
 
  Complexity:
    Average case : O(N)
    Worst case    : O(N^2)  (rare, occurs with consistently bad pivots)
 
