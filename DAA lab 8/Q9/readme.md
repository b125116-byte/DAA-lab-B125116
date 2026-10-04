Structure: the program is split into functions. collatz_next does one step with an overflow check. analyse follows a trajectory and records its steps and peak value. interval handles a range [a, b].

Overflow handling: values are unsigned long long. Before computing 3n+1, the program checks n > (ULLONG_MAX-1)/3 and reports an overflow instead of wrapping silently.

Interval mode: a dynamically allocated memo table stores the step count for every start value. For each start s, the loop only runs until the value drops below s, then reuses the stored result. This makes it fast over large ranges.

Usage: enter 1 n for a single trajectory, or 2 a b for an interval.

Test: n = 27 takes 111 steps and peaks at 9232. Over [1, 1,000,000], 837799 has the longest trajectory at 524 steps.
