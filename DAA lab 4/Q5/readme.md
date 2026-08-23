An interval has a start and end, such as (1, 3).

Example:
(1,3), (2,6), (8,10), (7,18)

Intervals (1,3) and (2,6) overlap, so merge them into:
(1,6)

Intervals (8,10) and (7,18) also overlap, so merge them into:
(7,18)

Final result:
(1,6), (7,18)

Simple approach:

Sort intervals by starting point.
Start with the first interval as the current interval.
Compare the next interval with it.
If they overlap, extend the current interval’s ending point.
If they do not overlap, output the current interval and start a new one.
Two intervals overlap when:
next.start <= current.end

Sorting takes O(n log n); merging in one pass takes O(n).
