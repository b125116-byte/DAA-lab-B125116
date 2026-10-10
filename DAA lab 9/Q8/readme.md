Plain problem: how many meetings are happening at the same time at most? That equals the rooms needed.

Algorithm: sort start times and end times separately. Sweep through starts: if the earliest unfinished end time is ≤ this start, a room frees up (reuse; move end pointer), otherwise open a new room. 
Complexity: two sorts: O(n log n), sweep O(n), space O(n).
