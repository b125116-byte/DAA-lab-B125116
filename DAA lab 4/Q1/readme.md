Stable sorting by three colours - O(n)

Every item has a number and a colour. The input is already in increasing number order. Put all reds first, then blues, then yellows. Importantly, do not change the relative order of items of the same colour. That last condition is called **stable** sorting.

Make three empty lists: `red`, `blue`, and `yellow`. Read each item once and append it to its matching list. Finally print the three lists in that order. Since appending never changes order, numbers inside each colour remain sorted.

There is one pass through the `n` items, followed by printing at most `n` items.Therefore time complexity O(n).


6
1 R
2 B
3 R
4 Y
5 B
6 R


Result: `(1,R) (3,R) (6,R) (2,B) (5,B) (4,Y)`
