Idea: ways[v] is the number of combinations that sum to v. Process one coin at a time and update ways[v] += ways[v-c]for v = c..V.

Why the loop order matters: the coin loop must be the outer loop. That way each multiset is counted once, so 1+2 and 2+1 are the same. Swapping the loops would count ordered sequences instead.

Complexity: O(n·V) time, O(V) space. I used unsigned long long because counts grow quickly.

Test: {1, 2, 3} with V = 4 gives 4.
