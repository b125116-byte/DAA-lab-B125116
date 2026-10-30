Approach. Put all K hubs into the queue at distance 0 with owner equal to their index, then run an ordinary BFS. Each vertex is reached first at its true dmin, and it inherits its parent’s owner. 
Vertices are not expanded beyond distance R, so everything farther stays at owner = −1.

Tie-breaking. Several hubs can reach a vertex u at the same distance. When a second parent at distance d−1 reaches an already-labelled u, the code keeps the smaller owner index. 
This is safe because every vertex at level d−1 is popped before any vertex at level d, so each vertex’s owner is final by the time it is expanded.

Input. The input is n m K R, then the K hubs, then m undirected edges (1-indexed), stored as an adjacency list. The output is owner and dist for every vertex.

Complexity. Each vertex is enqueued once and each edge is looked at twice, 
so time is O(V + E + K) and space is O(V + E). 
This is far better than running K separate BFS runs, which would cost O(K·(V+E)).
