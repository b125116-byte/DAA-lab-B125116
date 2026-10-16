Bipartite means you can colour every vertex red or blue so that every edge joins different colours. An odd cycle makes that impossible.

Idea: a normal DSU only knows “same group or not.” We also store a parity for each vertex: its colour relative to its parent. After path compression, that becomes its colour relative to the root.

For a new edge (u, v):

If u and v are in different groups, merge them. Set the parity of the attached root so that u and v end up with different colours.
If they are in the same group and have the same colour, the edge closes an odd cycle. Reject it.
If they are in the same group with different colours, the edge is fine. Accept it.

Complexity: O(α(V)) per edge, so O(E·α(V)) total. 
Space is O(V).
