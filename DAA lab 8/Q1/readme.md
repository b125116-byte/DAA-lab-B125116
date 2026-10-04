 Q1: Minimum Coin Change (unbounded)
  Idea: dp[v] is the fewest coins needed to make amount v. Try every coin c ≤ v as the last coin: dp[v] = 1 + min(dp[v-c]), with dp[0] = 0. If dp[V] is still infinity, print −1.
Input: n, then the n coin values, then V.
Extra: the program also prints which coins were used.
Complexity: O(n·V) time, O(V) space. This is pseudo-polynomial, since V is a value rather than an input length.
Test: coins {1, 2, 5} with V = 11 gives 3 (5+5+1).
