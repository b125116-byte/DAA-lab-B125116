
   Q3: Reve's puzzle -- Tower of Hanoi with 4 pegs, n disks
  
   INPUT REPRESENTATION
   ---------------------
   n = number of disks (labelled 1..n, 1 = smallest).
   4 pegs labelled 0,1,2,3. A peg's state is a stack (array)
   of disk sizes, smallest on top.

   KEY IDEA (Frame-Stewart algorithm)
   --------
   With only 3 pegs the optimal move count is 2^n - 1.
   With a 4th peg we can be smarter: pick some k (0<=k<n),
     1) move the TOP k disks from source to a spare peg,
        using all 4 pegs recursively            -> f(k) moves
     2) move the remaining (n-k) LARGEST disks from source to
        destination using the classic 3-peg algorithm (the 4th
        peg is unusable now because it holds the k small disks)
                                                  -> 2^(n-k) - 1 moves
     3) move the k disks from the spare peg onto the destination,
        again using all 4 pegs recursively       -> f(k) moves
   So:      f(n) = min over k of  [ 2*f(k) + 2^(n-k) - 1 ]
            f(0) = 0
   We try every k from 0..n-1 and keep the best -- this is the
   Frame-Stewart recurrence, proven optimal for up to 4 pegs by
   Bousch (2014). For n = 8 disks this gives f(8) = 33, matching
   the puzzle's classic name "Reve's puzzle in 33 moves".

   COMPLEXITY
   ----------
   Computing f(1..n) via DP: O(n^2) time, O(n) space.
   Actually EXECUTING the moves (printing them) takes
   O(2^n) time in the worst 3-peg sub-calls -- inherent to the
   problem since that many moves really are produced.
   =========================================================== */
