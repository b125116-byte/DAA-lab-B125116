
   Q4: Security switches
   
   INPUT REPRESENTATION
   ---------------------
   n switches, state array sw[0..n-1]. 1 = ON, 0 = OFF, all
   start ON. We number them so that "switch 1" is the RIGHTMOST,
   unconstrained switch (rule i) and "switch n" is the LEFTMOST
   one; sw[i-1] in the array is printed at screen-position i-1
   (left to right), so switch 1 is printed first, switch n last
   -- i.e. printed left-to-right the array shows switch
   1,2,...,n, which visually is the mirror of physical
   left/right, but the LOGIC is unaffected by which end you
   call "left": what matters is that switch 1 is unconstrained
   and switch n needs its right neighbour to satisfy rule (ii).

   KEY IDEA
   --------
   Read the switch pattern left-to-right as an n-bit binary
   number: this is *exactly* the standard binary-reflected
   Gray code! Rule (ii) -- "you may flip switch i only if the
   switch to its immediate right is ON and every switch to the
   right of THAT is OFF" -- is precisely the legality rule that
   lets you step from one Gray-code word to the next.

   Recursive solution (mirrors how Gray code is built):
       solve(n):      
           if n == 0: return
           solve(n-1)      
           toggle switch n
           restore(n-1)    
       restore(n):    
           if n == 0: return
           solve(n-1)
           toggle switch n
           restore(n-1)
   Both procedures only ever toggle a switch when rule (ii)'s
   condition holds, and together they realize the SHORTEST path
   between the all-ON and all-OFF Gray-code words -- exactly
   2^n - 1 moves, which is provably optimal.

   COMPLEXITY
   ----------
   Exactly 2^n - 1 toggles performed -> O(2^n) time, O(n) space
   (recursion depth). This exponential cost is inherent: 2^n - 1
   really is the minimum number of moves needed.


