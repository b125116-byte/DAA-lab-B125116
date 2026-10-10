Plain problem: odd x → 2x (once, since 2x is even); even x → x/2 (as long as even). Minimise max − min.

Key trick: an odd number can only ever be doubled once, and then it can only be halved back. So double all odd numbers first; now every number can only go down (halve). The max is the problem, so repeatedly halve the max (max-heap) while it's even, updating min and the best deviation. Stop when the max is odd (it can't be lowered). Complexity: each element can be halved at most log M times, each with a heap operation:
O(n log n · log M);
space O(n).
