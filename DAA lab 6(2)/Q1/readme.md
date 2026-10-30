Plain recursion recomputes the same values again and again, which takes exponential time. 
DP stores each result once: dp[i] = dp[i-1] + dp[i-2], filled from dp[0]=0 and dp[1]=1 up to n.

Complexity: time O(n), space O(n). Keeping only the last two values would reduce space to O(1).
Limit: unsigned long long holds the answer up to n = 93, so the program rejects larger n.
