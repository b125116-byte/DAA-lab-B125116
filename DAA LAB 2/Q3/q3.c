#include <stdio.h>
#include <stdlib.h>

// Global variable to isolate structural comparison operations
long long performance_steps = 0;

// Base comparison tracking simulator
// Merging array block A and B requires up to (sizeA + sizeB) elements traversal steps
void track_merge_cost(int size1, int size2) {
    performance_steps += (size1 + size2);
}


// METHOD 1: REPEATED SEQUENTIAL MERGING [Complexity: O(n * k^2)]

long long evaluate_sequential_merging(int k, int n) {
    performance_steps = 0;
    int current_merged_size = n;
    
    // Sequentially merge the remaining k-1 arrays one by one
    for (int i = 1; i < k; i++) {
        track_merge_cost(current_merged_size, n);
        current_merged_size += n; // Result grows linearly by n elements each loop
    }
    return performance_steps;
}


// METHOD 2: DIVIDE & CONQUER PAIRWISE MERGING [Complexity: O(k * n * log k)]

long long evaluate_pairwise_merging(int k, int n) {
    performance_steps = 0;
    int current_active_arrays = k;
    int current_block_size = n;
    
    // Process pairs of arrays layer by layer
    while (current_active_arrays > 1) {
        int pairs_to_merge = current_active_arrays / 2;
        
        for (int i = 0; i < pairs_to_merge; i++) {
            track_merge_cost(current_block_size, current_block_size);
        }
        
        // Handle odd number of arrays (the odd one carries over to next layer)
        if (current_active_arrays % 2 != 0) {
            current_active_arrays = pairs_to_merge + 1;
        } else {
            current_active_arrays = pairs_to_merge;
        }
        
        // The array block size doubles at each logarithmic step layer
        current_block_size *= 2;
    }
    return performance_steps;
}

// MAIN BENCHMARK ENGINE

int main() {
    int fixed_element_size = 50; // Total elements inside each individual array (n)
    
    printf("=================================================================\n");
    printf(" BENCHMARKING MULTI-WAY SORTED ARRAY MERGING CONSTRAINTS\n");
    printf(" Fixed Elements Per Array (n) = %d\n", fixed_element_size);
    printf("=================================================================\n");
    printf("%-10s | %-22s | %-22s\n", "Arrays (k)", "Method 1 (Sequential)", "Method 2 (Pairwise)");
    printf("-----------------------------------------------------------------\n");

    // Loop through escalating counts of arrays (k) up to 64
    for (int current_k = 2; current_k <= 64; current_k *= 2) {
        long long sequential_steps = evaluate_sequential_merging(current_k, fixed_element_size);
        long long pairwise_steps = evaluate_pairwise_merging(current_k, fixed_element_size);
        
        printf("%-10d | %-22lld | %-22lld\n", current_k, sequential_steps, pairwise_steps);
    }
    
    printf("=================================================================\n");
    return 0;
}
