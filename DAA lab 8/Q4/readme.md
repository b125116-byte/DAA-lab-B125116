Idea: dp[i] is the length of the longest increasing subsequence ending at a[i]: 1 + max dp[j] over j < i with a[j] < a[i]. A parent array lets the program rebuild one actual subsequence.
Faster variant, also included: keep tails[k], the smallest possible tail of an increasing subsequence of length k+1, and binary-search each element into it.

Complexity: the DP is O(n²) time and O(n) space. The tails method is O(n log n) time.

Test: the array {10, 22, 9, 33, 21, 50, 41, 60} gives length 5.
