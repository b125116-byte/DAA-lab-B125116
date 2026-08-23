You are given intervals on a number line. Find a point contained in the largest number of intervals.

Example:
(10,40), (20,60), (50,90), (15,70)

At point 50:
(20,60) contains 50
(50,90) contains 50
(15,70) contains 50

So point 50 is in 3 intervals.

Simple approach:
Mark every left endpoint as +1 because an interval begins there.
Mark every right endpoint as -1 because an interval ends there.
Sort these endpoints.
Scan from left to right, keeping a count of currently active intervals.
Whenever the count becomes the largest, save that point.

Important: the question says endpoints count as part of the interval. So if one interval ends at 50 and another begins at 50, both count at point 50. Therefore, process a start event before an end event at the same point.

This is also O(n log n) because sorting is the main operation.
