A DSU is good at merging but bad at splitting, and deleting vertices splits components. So run time backwards:

The last state has every vertex deleted, so the answer there is 0.
Walk the deletion order from the end. Each step adds a vertex back, which only needs unions.
Before adding p_i, the graph is exactly what remains after deleting p_i. So ans[i] = best is recorded first, and then p_i is added.
After adding p_i and merging with its active neighbours, only the component containing p_i can have changed. Update best with its sum.

This is why we need an adjacency list: to find the neighbours of the vertex being added back. The code assumes non-negative weights.

Complexity: O((V + E)·α(V)).
Space is O(V + E).
