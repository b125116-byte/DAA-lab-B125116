Each person has:

entry time a
exit time b

Example:
Person 1: 1 to 8
Person 2: 2 to 5
Person 3: 4 to 9
Person 4: 6 to 10

At time 4, persons 1, 2, and 3 are present. So 3 people are present, which is the maximum.

Simple approach:
Treat every entry as +1.
Treat every exit as -1.

Sort all these events by time.

Move through the events while maintaining a count of people currently inside.
Whenever the count becomes the largest so far, save that time.
For the example:
time 1: +1 → 1 person
time 2: +1 → 2 people
time 4: +1 → 3 people  ← maximum
time 5: -1 → 2 people

Sorting events costs O(n log n), and scanning them costs O(n).
