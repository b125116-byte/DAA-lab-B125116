Let dp[i][w] be the best profit using the first i items with capacity w. For item i there are two choices:

Skip it: dp[i-1][w].
Take it (only if its weight ≤ w): dp[i-1][w - wt[i]] + profit[i].

The cell stores the larger of the two. The answer is dp[n][W]. The code also backtracks through the table to print which items were chosen.

Input: n W, then the n weights, then the n profits.
Complexity: time O(n·W), since there are (n+1)(W+1) cells at O(1) each. 
Space is O(n·W), or O(W) with a single rolling row if you don’t need the item list. The time is pseudo-polynomial, because it depends on the value of W rather than its bit length.
Test: weights 1 3 4 5, profits 1 4 5 7, W = 7 gives profit 9 using items 2 and 3.
