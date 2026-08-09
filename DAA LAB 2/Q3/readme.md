Merge k sorted arrays — sequential method

Algorithm:
Merge array 1 and array 2.
Merge that result with array 3.
Merge the new result with array 4.
Continue until all k arrays are merged.
The merge sizes are:

2n, 3n, 4n,....,kn
So total work is:

n(2 + 3 + .... + k) = \Theta(nk^2)
This is simple but inefficient when k is large, because early elements are merged repeatedly.


3(b). Merge k sorted arrays — pairwise/balanced method
Algorithm:
Pair neighboring arrays and merge each pair.
Pair the resulting arrays and merge again.

Repeat until only one array remains.
Level 1: 8 arrays → 4 merged arrays
Level 2: 4 arrays → 2 merged arrays
Level 3: 2 arrays → 1 final array

At every level, all kn elements are processed once. There are log₂ k levels:

\Theta(kn\log k)
So this method is much better than sequential merging:

Sequential: Θ(nk²)
Pairwise balanced merge: Θ(nk log k)
Sequential: Θ(nk²)
Pairwise balanced merge: Θ(nk log k)
