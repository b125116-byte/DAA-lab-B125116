  
    n x n square matrix operations and their worst-case complexities
   ============================================================
   (i)   addition               -> O(n^2)
   (ii)  multiplication         -> O(n^3)  (naive; Strassen ~O(n^2.81))
   (iii) zero-matrix check      -> O(n^2)
   (iv)  symmetric check        -> O(n^2)
   (v)   determinant            -> O(n^3)  (Gaussian elimination;
                                    naive cofactor expansion is O(n!))
   (vi)  transpose in place     -> O(n^2)
   (vii) eigenvalue/eigenvector -> no closed form for n>4 in general;
                                    iterative methods used. Power
                                    iteration used here: O(n^2) per
                                    iteration (dominant eigenpair only).
                                    Full spectrum via QR algorithm costs
                                    O(n^3) per iteration.
