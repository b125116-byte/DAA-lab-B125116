 
   Convolution of vectors A (length m) and B (length n), n >= m,
   in O(n log n) using a divide-and-conquer FFT (Cooley-Tukey).
   ============================================================
   Idea:
   
   - The direct definition C[k] = sum_j A[j]*B[k-j] is a polynomial
     multiplication: if A and B are coefficient vectors of polynomials
     p(x) and q(x), then C is exactly the coefficient vector of p(x)*q(x).
     
   - Evaluate p and q at enough points, multiply pointwise (O(N)),
     then interpolate back. The FFT does exactly this "evaluate /
     interpolate" using N-th roots of unity in O(N log N) via the
     classic divide-and-conquer recursion:
        FFT(coeffs) = combine( FFT(even-indexed coeffs),
                                FFT(odd-indexed coeffs) )
     
   - Pad both vectors with zeros to a length N = next power of 2
     that is >= m+n-1 (the true length of the convolution).
     
   - Total cost: 2 forward FFTs + 1 inverse FFT + O(N) pointwise
     multiply = O(N log N) = O(n log n) since N = O(n).
