Idea: D[i][j] is the fewest operations to turn A[0..i) into B[0..j). The base cases are D[i][0] = i (delete everything) and D[0][j] = j (insert everything). If the characters match, D[i][j] = D[i-1][j-1]. Otherwise it is 1 + min(replace, delete, insert).

Traceback: walk back from (m, n), checking which neighbour produced each cell's value. The program prints the operations in forward order.

Complexity: O(mn) time and space. The full table is needed for the traceback.

Test: "horse" to "ros" gives 3.
