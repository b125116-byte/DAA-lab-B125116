
   Q7: Matrix Chain Multiplication (MCM)

   INPUT REPRESENTATION
   ---------------------
   An array p[0..k] of dimensions: matrix A_i has dimensions
   p[i-1] x p[i], for i = 1..k. (k matrices in the chain.)

   KEY IDEA
   --------
   m[i][j] = minimum scalar multiplications to compute the
             product A_i * A_{i+1} * ... * A_j.
   To multiply the chain from i to j, pick a SPLIT point s
   (i <= s < j): first multiply A_i..A_s, then A_{s+1}..A_j,
   then multiply the two resulting matrices together:
        m[i][j] = min over s of
             m[i][s] + m[s+1][j] + p[i-1]*p[s]*p[j]
   Base case: m[i][i] = 0 (single matrix needs no multiplication).
   We also store split[i][j] = the best s, to reconstruct the
   optimal parenthesization afterwards.

   COMPLEXITY
   ----------
   O(k^3) time  (k^2 subproblems, each takes O(k) to minimize
                 over the split point)
   O(k^2) space (for the m[][] and split[][] tables) 
