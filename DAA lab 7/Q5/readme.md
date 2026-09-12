
   Q5: Hitting a moving target
   
   INPUT REPRESENTATION
   ---------------------
   n hiding spots numbered 1..n on a line. We track the target
   only through a SET of "still possible" positions (a boolean
   array possible[1..n]) -- we never see the target directly.

   KEY IDEA
   --------
   Such a guaranteed-hit algorithm DOES exist for every n >= 2.
   Reasoning: between any two consecutive shots the target's
   position changes by exactly +/-1, so its PARITY (odd/even)
   flips every turn. We don't know the target's starting parity,
   so first we hunt assuming it started on an "expandable" track
   sweeping inward, then repeat sweeping back -- concretely the
   sequence
        2, 3, 4, ..., n-1, n-1, n-2, ..., 3, 2      (n >= 3)
   is guaranteed to hit the target regardless of where it starts
   and however it decides to move at each step. (For n = 2 the
   trivial sequence "shoot spot 1 twice" suffices.)

   Why it works (sketch): after the increasing sweep
   2,3,...,n-1, any target that started at an EVEN position is
   caught (its position always matches the shot's parity at
   the right time). The decreasing sweep n-1,...,3,2 that
   follows performs the mirror-image hunt and catches any
   target that started at an ODD position. Together every
   possible start is eliminated.

   VALIDATION METHOD IN THIS PROGRAM
   ----------------------------------
   Rather than trust the argument alone, the program tracks the
   SET of positions the target could still occupy (starting as
   "all of 1..n", since we don't know where it starts or which
   way it will move) and simulates: after each shot, remove that
   position from the possible set (a hit there means the target
   is caught), then "diffuse" the remaining possible positions
   to their neighbours (since the target must move). If the
   possible set becomes empty, a hit is guaranteed.

   COMPLEXITY
   ----------
   The firing sequence has 2n-4 shots (n>=3) -> O(n).
   Each simulation step touches O(n) positions -> overall
   verification costs O(n^2), just to double-check optimality;
   actually carrying out the algorithm is O(n).
