Coordinate flattening: a DSU works on numbers, not (row, col) pairs, so cell (r, c) becomes id = r*C + c.

Idea: keep a counter count.

When you add land, do count++, because it starts as its own island.
Look at its 4 neighbours. For each neighbour that is land, try to union. If the union actually merged two different groups, do count--.
If the cell was already land, change nothing.

Complexity: O(R·C) to initialise, then O(4·α(RC)) per addition, so O(RC + k·α(RC)) total. 
Space is O(RC).
