Problem with the naive graph. Comparing all word pairs costs O(N²·L), which is far too slow for N = 10⁵.

Wildcard buckets. For each word, make its L patterns by replacing one position with *, so hot gives *ot, h*t and ho*. Two words differ in exactly one character if and only if they share a pattern. I generate all N·L patterns and sort them, which groups matching words together. Each word stores the group id of each of its patterns.

Bidirectional BFS. I search from A and from B at the same time and always expand the smaller frontier. A full level is expanded before checking for a meeting, and the minimum of dist_A + 1 + dist_B over all meetings is taken, so the answer is exact.

Key optimization. Each pattern group is scanned only once per search direction. Without this, a group with many words (such as *ot) could be rescanned for every member, which would be too slow.

Edge cases handled:

B not in D gives −1.
A = B gives 0.
A need not be in D; it is added as an extra node.

Input. The input is N, then N words, then A B.

Complexity. Pattern generation and sorting cost O(N·L·log(N·L)), and the BFS costs O(N·L) because each group is scanned once per side. Space is O(N·L). Bidirectional search also reduces the explored region in practice, from roughly b^d to 2·b^(d/2).

All three programs use scanf for input, so you can pipe a test file into the compiled binary with ./a.out < input.txt.
