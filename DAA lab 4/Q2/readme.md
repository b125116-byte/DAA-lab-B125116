 Pair from two sets whose sum is x - O(n log n)

 Pick exactly one value from S1 and exactly one from S2. Check whether their sum is the target x.

If we choose a from S1, the value needed from S2 is x - a. Sort S2 then binary search for that needed value for every value in S1.

 Sorting S2 costs O(n log n). We perform `n` binary searches, and each costs O(log n), for another O(n log n).Therefore time complexity = O(nlogn).

