Plain problem: e.g. "aabbcc", K=3 → "abcabc". Same letters must be ≥ K positions apart.

Greedy: fill positions left to right. At each position choose, among letters that are allowed (last used at least K positions ago), the one with the most copies left. 
Frequent letters are the hardest to place, so we use them whenever possible. 
If nobody is allowed → return "" (impossible). 
Complexity: the code scans 256 characters per position: O(n·σ). Space O(n + σ).
With a max-heap plus a waiting queue of "cooling down" letters it becomes O(n log σ). 
