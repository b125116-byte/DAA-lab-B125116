Plain problem: The car starts with fuel F (so it can drive F units). 
Stations at distance d_i give f_i extra fuel. Reach D with the fewest stops.

Reverse greedy trick: drive forward and don't decide to stop yet; just remember every station you pass (in a max-heap). 
When you can't go further, pretend you stopped at the passed station with the most fuel. Repeat. 
If the heap is empty while you're stuck → unreachable (−1). 
Why it works: to cover the same distance with the fewest stops you always want the biggest refill among stations you could have used. 
Complexity: sort O(m log m) + each station pushed/popped once O(m log m) = O(m log m).
