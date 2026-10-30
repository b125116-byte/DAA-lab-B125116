With N entries in arr[], there are N−1 matrices, and matrix i has size arr[i-1] × arr[i]. Let m[i][j] be the minimum cost to multiply matrices i through j. Trying every split point k between i and j gives:

m[i][j] = min over k of ( m[i][k] + m[k+1][j] + arr[i-1]·arr[k]·arr[j] )

with m[i][i] = 0. The table is filled by increasing chain length, so the smaller subchains are ready when needed. A second table s[i][j] records the best k, which lets the program print the best bracketing.

Input: N, then arr[0..N-1].
Complexity: there are O(N²) subproblems, each trying O(N) splits, so time is O(N³) as the sheet says. Space is O(N²).
Test: {10, 30, 5, 60} gives 4500 with the order ((A1 x A2) x A3). That costs 10·30·5 + 10·5·60 = 1500 + 3000 = 4500. 
The other order, A1 x (A2 x A3), costs 30·5·60 + 10·30·60 = 27000, which is much worse.
