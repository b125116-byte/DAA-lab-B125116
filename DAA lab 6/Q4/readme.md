
   Sorting a permutation using only reverse(p, i, j).
 
   PART 1 - O(n) reversals suffice (pancake-sort style):
     For size = n down to 2:
        find index of the maximum element among p[0..size-1]
        reverse(p, 0, maxIdx)      -- brings the max to the front
        reverse(p, 0, size-1)      -- sends it to its final position
     Each of the (n-1) rounds uses at most 2 reversals, so the total
     number of reversals is O(n) (at most 2n-2). This proves any
     permutation can be sorted in O(n) reversal OPERATIONS (ignoring
     their cost/length).
 
   PART 2 - O(n log^2 n) COST (cost of reverse(p,i,j) = j-i+1):
     Run ordinary merge sort (T(n) = 2T(n/2) + merge). Instead of
     merging with an auxiliary array, merge the two sorted halves
     in place using only rotations - and a rotation of a block is
     implemented with exactly 3 reversals:
        rotate(p, first, middle, last):
            reverse(p, first, middle)
            reverse(p, middle, last)
            reverse(p, first, last)
            
     A naive in-place merge that rotates one element at a time costs
     O(n^2). Instead we use the standard binary-search-driven in-place
     merge (as used in std::inplace_merge): at each recursive step we
     binary-search for a split point (O(log n) comparisons) and
     perform ONE rotation, then recurse on the two remaining pieces.
     This merges k elements at reversal-cost O(k log k).

      Recurrence for the whole sort:
        T(n) = 2 T(n/2) + O(n log n)   [merge cost at this level]
             = O(n log^2 n)
     which matches the required bound. Correctness follows directly
     from standard merge-sort correctness plus the fact that rotate
     (3 reversals) exactly implements a block swap, so the in-place
     merge produces the same sorted result as an ordinary merge.
 
     
     (3 reversals) exactly implements a block swap, so the in-place
     merge produces the same sorted result as an ordinary merge.
