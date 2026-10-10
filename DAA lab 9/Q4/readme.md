Plain problem: joining sticks x and y costs x+y. 
Sticks joined early get "paid for" again every time they're part of a later join, so short sticks should be joined first and long sticks last.

Algorithm: min-heap; repeatedly pop two smallest, add their sum to the cost, push the sum back. 
(Identical to Huffman — the total cost = Σ length × (number of joins it takes part in) = Σ length × depth.) 
Example: {2,4,3,6} → 2+3=5, 4+5=9, 6+9=15 → total 29. 
Complexity: O(n log n), space O(n).

* Use long long to avoid overflow.
