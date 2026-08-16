Normal matrix multiplication divides each matrix into four blocks and performs 8 recursive multiplications.
Strassen reduces this to 7 multiplications. For block matrices:
A =  A11  A12          B = B11   B12   
     A21  A22              B21   B22
it computes seven intermediate products, then combines them to obtain the four blocks of C = A × B.

T(n)=7T(n/2)+O(n^2)

T(n)=O(n^{\log_2 7}) ~ O(n^{2.807})
This is asymptotically faster than normal multiplication, which is O(n^3).
