The DSU stores each component’s size and total weight. The catch is that a component can be valid (size ≤ K) now and become invalid (too big) after a merge. 
So the answer can go down, and a simple running maximum would be wrong. 
For example, in my test with K=2 the answer goes 10, 14, then “none.”

Idea: keep a max-heap of snapshots (weight, root, size). 
Whenever the top of the heap is stale, discard it. A snapshot is stale if its root is no longer a root, its size has changed, or its size exceeds K. This is called lazy deletion. Then the top of the heap is the answer.

The edge weights don’t affect connectivity, so the code reads them and ignores them.

Complexity: the heap gets at most 2V entries, so O((V + E) log V) in total, plus the DSU work. 
Space is O(V).
