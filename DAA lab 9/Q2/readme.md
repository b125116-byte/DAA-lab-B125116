Plain problem: give frequent symbols short bit-strings and rare symbols long ones, so that no code is a prefix of another (so decoding is unambiguous), minimising total bits.

Algorithm: put all symbols in a min-heap by frequency. 
Repeat: remove the two smallest, make a parent whose frequency is their sum, push it back. The tree's leaf depths are the code lengths. 
Canonical form: keep only the lengths, sort symbols by (length, symbol), give the first symbol all zeros, and for each next symbol do code = (code+1) << (extra length). This makes the codebook reproducible from lengths alone (that's what ZIP/JPEG store).

Why greedy works: the two rarest symbols can always be siblings at the deepest level (exchange argument), so merging them first is safe. 
Input representation: n and (symbol, frequency) pairs; heap of node indices; arrays Lc[], Rc[] for children. 
Complexity: 2n−1 heap operations × O(log n) = O(n log n); canonical sort O(n log n) (insertion sort in the code is O(n²), fine for n ≤ 256).
