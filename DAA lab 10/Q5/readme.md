Key fact: if positions are connected by swaps, they can be rearranged into any order. So each connected component is a “free pool” of positions and values.

Idea: to make the permutation smallest, put the smallest values in the earliest positions of each component.

Union all the swap pairs to find the components.
Sort the values by (component, value).
Sort the positions by (component, position).
Match them up: the i-th value goes to the i-th position. Both lists are grouped the same way, so this works inside every component at once.

In my test, A = [4,3,2,1] with swaps (1,2) and (3,4) gives [3,4,1,2]. You cannot move 1 or 2 into the front half, since they live in the other component.

Complexity: O(m·α(n) + n log n), dominated by the sorting. 
Space is O(n).
