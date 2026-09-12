
   Q6: The best time to be alive
   
   INPUT REPRESENTATION
   ---------------------
   n scientists, each given as a pair (birth[i], death[i]) --
   the years they were alive, inclusive.

   KEY IDEA (sweep-line / difference-array technique)
   --------
   Instead of checking, for every candidate year, how many
   scientists were alive (an O(n * range) brute force), turn
   each scientist's lifespan into two EVENTS:
        at year birth[i]      : +1  (one more scientist alive)
        at year death[i] + 1  : -1  (this scientist no longer alive)
   (we use death+1 because the problem says if A dies the same
   year B is born, A's death is considered to happen BEFORE B's
   birth, i.e. they are NOT simultaneously alive that year --
   so the "alive count" for A should stop exactly at the start
   of that shared year, matching a delta of -1 placed at death+1
   fed through a sweep that applies -1 events before +1 events
   in the same year... equivalently: sort events by year, and
   when years tie, process ALL the -1 (death) events before any
   +1 (birth) events of that year.)

   Sort all 2n events by year (ties: deaths before births).
   Sweep through them left to right, maintaining a running
   "currently alive" counter; the year(s) where this counter
   peaks is the "best time to be alive".

   COMPLEXITY
   ----------
   Sorting 2n events: O(n log n).
   One linear sweep: O(n).
   Total: O(n log n) time, O(n) space -- versus the naive
   O(n * (maxYear-minYear)) approach.

int main(void) {
