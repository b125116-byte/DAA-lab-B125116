Approach :
Plain problem: Classic fractional knapsack: fill a bag of capacity W with parts of items to maximise value; best strategy is to take items by highest value per kg (density). Twist: each item's density shrinks the longer you wait: v/w − λ·t.

Why greedy: without decay, it is the standard exchange argument (swapping a low-density kg for a high-density kg never hurts). With decay, we apply it to the current densities. Be honest in your report: with the "density at the moment of pickup" model this is the natural greedy; a fully rigorous optimality proof depends on how you define value while an item is being consumed.

Input representation: arrays v[], w[], λ[], plus used[]. Complexity: n rounds × O(n) scan = O(n²). 
(A plain heap can't be used because the keys change with t. Without decay, sort once: O(n log n).)
