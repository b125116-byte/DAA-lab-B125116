Tools used for graph plotting - GNUplot.
Finding time complexity :
Standard merge sort: T(n) = 2T(n/2) + O(n) → O(n log₂n).
Modified merge sort splits into thirds: T(n) = 3T(n/3) + O(n). 
The merge step (combining 3 sorted runs) still touches every element a constant number of times, so it's still O(n) work per level. 
By the Master theorem (a=3, b=3, f(n)=O(n)): O(n log₃n).
Since log₃n = log₂n / log₂3, this is still Θ(n log n) — same asymptotic class, just a smaller constant (log₃n < log₂n by a constant factor ≈ 0.63). 
The three-way merge does more comparisons per merge step (up to 2 comparisons per element instead of 1). 
So in practice the constant-factor trade-off roughly cancels out — it's a wash, not a real improvement.
Both scale identically (Θ(n log n)) with the 3-way version consistently a bit slower in practice due to the extra comparisons per merge step, confirming the theory.
