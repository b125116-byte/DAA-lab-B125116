
   Invert the coin-triangle
 
   INPUT REPRESENTATION
   ---------------------
   A triangle of side n packed with pennies has coins at every
   lattice point (r, c) with 0 <= r <= n-1 (row, 0 = apex) and
   0 <= c <= r (position within the row). This pair of integers
   is enough to describe every coin -- we never need real (x,y)
   pixel coordinates.

   KEY IDEA
   --------
   Place both the "apex-up" triangle UT(n) and the "apex-down"
   triangle DT(n) on the SAME (r,c) index grid:
        UT(n) = { (r,c) : 0<=c<=r          }   (lower triangle)
        DT(n) = { (r,c) : r<=c<=n-1         }   (upper triangle)
   Both are subsets of the n x n grid of (r,c) pairs.
   A coin that is in UT(n) *and* in some translate of DT(n)
   never has to move -- we just reinterpret it as belonging to
   the inverted triangle. So:

        moves(n) = n(n+1)/2  -  (largest overlap between UT(n)
                                   and any translate of DT(n))

   The program brute-force searches every integer translate
   (a,b) to find that largest overlap, which validates the
   compact closed-form formula we derived analytically:

        M(n) = floor( n*(n+1) / 6 )

   (For n = 4, the classic "10-penny" pub puzzle, this gives
   M(4) = floor(20/6) = 3 -- matching the well-known answer.)

   COMPLEXITY
   ----------
   Brute force search over shifts (a,b) in [-n,n]x[-n,n], and for
   each shift scanning all O(n^2) coins of the triangle:
        O(n^4)  -- fine for validation on modest n.
   The closed-form formula evaluates in O(1).



    return 0;
}
