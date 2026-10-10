Plain problem: like Huffman, but leaves must stay in the given left-to-right order (needed for search trees, where order matters). So you can't merge any two smallest weights — only those that can be joined without crossing an original leaf.

Algorithm (Phase 1 of Hu–Tucker):

Keep a list; original leaves are "squares", merged nodes are "circles".
Two nodes are compatible if no square lies strictly between them.
Repeatedly merge the compatible pair with the smallest sum (leftmost on ties); the new circle sits at the left node's position.
Leaf depths of the resulting tree are the optimal depths; an alphabetic tree with exactly these depths exists and is rebuilt using a stack (Phase 3). Cost = Σ wᵢ·depthᵢ.

The code validates itself by comparing against a non-greedy O(n³) DP (MATCH printed). 
Complexity: this teaching version O(n³) (n rounds × O(n²) pair search).
Hu–Tucker's original paper achieves O(n log n) with a priority-queue method.
