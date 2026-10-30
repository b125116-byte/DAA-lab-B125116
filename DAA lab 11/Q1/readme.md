Key observation. Every weight is 0 or 1, so W(P) is simply the number of weight-1 edges, which is k₁(P). The penalty C therefore depends only on whether W(P) is odd. So Cost(P) = W(P) + C·[W(P) odd].

Approach. Split each vertex into two states, (v, 0) and (v, 1), where the second number is the parity of weight-1 edges used so far.

A weight-0 edge goes (v,p) → (u,p) at cost 0.
A weight-1 edge goes (v,p) → (u,1−p) at cost 1.

Run 0-1 BFS from (S,0) with a deque: 0-edges push to the front, 1-edges push to the back. For each vertex v the answer is min(dist[v][0], dist[v][1] + C). If both states are infinite, v is unreachable.

Input. The input is n m S C, then m lines u v w (1-indexed). I used an adjacency list, since 0-1 BFS needs fast iteration over out-edges.

Complexity. There are 2V states and 2E transitions, and each state is processed once, 
so time is O(V + E). Space is O(V + E).

The code treats paths as walks, so a vertex or edge may repeat. This is necessary, because the cheapest way to fix parity can involve revisiting a vertex.
