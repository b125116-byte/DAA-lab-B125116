 Question : To implement HeapSort to sort N randomly generated elements stored in a file.
 
  Steps:
    1. Generate N random numbers and write them to "input2.txt"
    2. Read the numbers back from the file into an array
    3. Build a max-heap, then repeatedly extract the max to sort
    4. Write the sorted result to "heap_sorted_output.txt"
 
  Complexity:
    Building the heap        : O(N)
    N extractions, each O(logN) : O(N log N)
    Total (best/average/worst) : O(N log N)   
    Space                     : O(1) extra (in-place)
 
