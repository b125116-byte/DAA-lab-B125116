Let L[i][j] be the LCS length of the first i characters of X and the first j characters of Y.

If X[i-1] == Y[j-1], then L[i][j] = L[i-1][j-1] + 1.
Otherwise L[i][j] = max(L[i-1][j], L[i][j-1]).

To print the subsequence itself, start at L[m][n] and walk back. A matching character is added to the result and the walk moves diagonally. Otherwise it moves toward the larger neighbour.

Input: two strings with no spaces, up to 1000 characters each.
Complexity: time O(m·n), space O(m·n).
Test: AGGTAB and GXTXAYB give length 4 and GTAB.
