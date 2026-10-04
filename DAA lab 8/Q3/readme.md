Idea: L[i][j] is the LCS length of the first i characters of X and the first j characters of Y. If the characters match, L[i][j] = L[i-1][j-1] + 1. Otherwise it is the larger of L[i-1][j] and L[i][j-1].

Reconstruction: walk back from (m, n). On a match, take the character and move diagonally. Otherwise move toward the larger neighbour.

Complexity: O(mn) time and space. Space drops to O(min(m, n)) if you only need the length.

Test: AGGTAB and GXTXAYB give length 4, "GTAB".
