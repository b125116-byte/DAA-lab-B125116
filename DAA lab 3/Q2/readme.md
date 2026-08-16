There are n coins; at most one is lighter, or all may be normal. 
Use a balance scale and divide-and-conquer.
Divide the coins into three nearly equal groups.
Weigh group 1 against group 2.
If one side is lighter, the defective coin is in that group.
If both sides balance, it is in group 3 - or there is no defective coin.
Repeat only on the suspected group.
Each weighing reduces the possible coins to about one third:

T(n)=T(n/3)+O(1)=O(log_3 n)

Keep one known-good coin to compare with the final candidate and decide whether it is actually lighter or normal.
