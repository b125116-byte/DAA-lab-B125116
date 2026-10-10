Plain problem: rule 1: everyone ≥ 1 candy; rule 2: higher rating than a neighbour ⇒ more candies than that neighbour.

Why two passes: each child has two neighbours. One scan can only enforce one side.

Left → right: if r[i] > r[i-1], c[i] = c[i-1] + 1.
Right → left: if r[i] > r[i+1], c[i] = max(c[i], c[i+1] + 1). 
Each child gets the smallest number satisfying both constraints, so the total is minimal. 
Example: ratings 1 0 2 5 3 2 2 → 2 1 2 3 2 1 1 = 12. 

Complexity: O(n) time, O(n) space.
