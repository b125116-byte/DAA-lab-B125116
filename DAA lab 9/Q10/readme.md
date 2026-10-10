The objective is to find the shortest string containing every input string as a substring. 
A common heuristic repeatedly merges the pair with the largest overlap.
Because the problem is not guaranteed to be solved optimally by this greedy strategy, this program is an experimental heuristic, not an exact solution.

Complexity: A straightforward implementation can take (O(n^2L)) time per merge-selection round, where \(L\) is the maximum string length. With up to \(n-1\) merges, the total is approximately (O(n^3L)), excluding the effects of substring removal and implementation details.

Important limitation: This is a heuristic implementation. The no-overlap case above stops further merging and concatenates remaining strings; therefore, the output is not guaranteed to be the shortest superstring.
An improved implementation would continue merging even when the maximum overlap is zero.
