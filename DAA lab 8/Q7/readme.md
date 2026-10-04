Idea: r[j] = max over i of (p[i] + r[j-i]), where i is the first piece cut. cut[j] records the best first piece, and following it back from n reconstructs all the piece lengths.

Complexity: O(n²) time, O(n) space.

Test: with prices {1, 5, 8, 9, 10, 17, 17, 20} and n = 8, the best revenue is 22, from pieces 2 + 6.
