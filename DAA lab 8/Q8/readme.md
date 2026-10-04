Idea: this follows the CLRS formulation. w[i][j] is the total probability weight of keys k_i..k_j plus their dummy keys. e[i][j] is the best expected cost of a tree on those keys. For each candidate root r, e[i][j] = min(e[i][r-1] + e[r+1][j] + w[i][j]). Subproblems are solved in order of increasing interval length.

Output: the program prints the minimum cost and the tree structure from the root[][] table.

Complexity: O(n³) time, O(n²) space. Knuth's optimisation (root[i][j-1] ≤ root[i][j] ≤ root[i+1][j]) brings it down to O(n²).

Test: the standard CLRS example gives 2.75 with k2 as the root.
