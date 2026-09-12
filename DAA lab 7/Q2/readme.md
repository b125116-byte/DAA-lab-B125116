
   Q2: Super egg-testing experiment (generalized E eggs, F floors)

   INPUT REPRESENTATION
   ---------------------
   Two integers E (number of eggs) and F (number of floors).

   KEY IDEA  (the "inverse" DP -- much faster than the classic
   O(E*F^2) egg-drop recurrence)
   --------
   Instead of asking "what's the min trials for F floors?",
   ask: "with e eggs and t trials/drops, what is the MAXIMUM
   number of floors I can fully resolve?"  Call this f(e,t).

   If I drop 1 egg from some floor with e eggs and t trials left:
     - it BREAKS   -> I have (e-1) eggs and (t-1) trials left,
                       and I've already located the floor within
                       the f(e-1, t-1) floors below.
     - it SURVIVES -> I still have e eggs and (t-1) trials, and
                       I can check f(e, t-1) MORE floors above.
   Together with the floor I just tested:
        f(e,t) = f(e-1,t-1) + f(e,t-1) + 1
   Base cases: f(0,t)=0 (no eggs -> resolve 0 floors),
               f(e,0)=0 (no trials -> resolve 0 floors).

   The answer to "min trials for E eggs, F floors" is the
   smallest t such that f(E,t) >= F.

   For E=2 eggs this reduces to the classic closed form
   T(T+1)/2 >= F, e.g. F=100 -> T=14.

   COMPLEXITY
   ----------
   f(e,t) filled for e=0..E, t=0..T_max: O(E * T_max) time and
   space, where T_max only needs to grow to about O(F^(1/E)),
   so for practical E,F this DP is extremely fast (in contrast
   to the O(E*F^2) "floors-first" DP).


    printf(" 14*15/2 = 105 >= 100, 13*14/2 = 91 < 100, so 14 is optimal.)\n");
    return 0;
}
