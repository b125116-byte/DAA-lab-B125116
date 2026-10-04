Idea: this is the same structure as Q4, but it tracks sums instead of lengths. S[i] = a[i] + max(S[j]) over j < i with a[j] < a[i], and the answer is the maximum of all S[i]. A parent array rebuilds the subsequence.

Complexity: O(n²) time, O(n) space. Sums are stored as long long.

Test: the array {1, 101, 2, 3, 100, 4, 5} gives 106 (1+2+3+100).
