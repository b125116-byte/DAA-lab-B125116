Tools used to plot the graph - GNUplot
A dictionary supports Search, Insert, Delete, Max, Min, Predecessor, Successor. The worst-case cost of each depends entirely on how you store the data:

Structure	Search	            Insert	Delete	Max/Min	Pred/Succ
Unsorted array	                O(n)	O(1)	O(1)*	O(n)	O(n)
Sorted array	              O(log n)	O(n)	O(n)	O(1)	O(1)
Singly linked, unsorted	        O(n)	O(1)	O(n)	O(n)	O(n)
Singly linked, sorted	          O(n)	O(n)	O(n)	Min O(1), Max O(n)	Succ O(1), Pred O(n)
Doubly linked, unsorted	        O(n)	O(1)	O(1)*	O(n)	O(n)
Doubly linked, sorted	          O(n)	O(n)	O(1)*	O(1)	O(1)

*Delete is O(1) whenever you're given a pointer/index to the element itself (as the ADT specifies) rather than a key — you don't need to search for it first, you just splice it out. In a singly linked list you still need the predecessor's next pointer, so it's O(n) there unless you keep a "previous" pointer around.

Insert is O(1) for unsorted structures (just append/prepend) and O(n) for sorted ones (you must find the right spot and shift/relink).

