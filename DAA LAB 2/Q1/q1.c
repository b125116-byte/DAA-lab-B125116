#include <stdio.h>
#include <stdlib.h>

// 1. TYPEDEFS & SYSTEM ARCHITECTURE

// Enum matching our structural indexing
typedef enum {
    UNSORTED_ARRAY = 0,
    SORTED_ARRAY,
    SLL_UNSORTED,
    SLL_SORTED,
    DLL_UNSORTED,
    DLL_SORTED,
    TOTAL_DS_COUNT
} DS_Type;

// Structural metadata tracker
typedef struct {
    DS_Type type;
    const char* name;
    int data_column; // Maps data columns inside the data file
} DS_Config;

// Absolute operational step counter
long long algorithmic_steps = 0;

// 2. SIMULATION ROUTINES (WORST CASE SEARCH)

void simulate_array_workload(int N, DS_Type type) {
    if (type == UNSORTED_ARRAY) {
        algorithmic_steps += N; // O(N) Linear Scan
    } else if (type == SORTED_ARRAY) {
        int temp = N;
        while (temp > 0) {
            algorithmic_steps++; // O(log N) Binary Search
            temp /= 2;
        }
    }
}

void simulate_sll_workload(int N, DS_Type type) {
    // Both sorted and unsorted SLL require a linear search walkthrough O(N)
    algorithmic_steps += N; 
}

void simulate_dll_workload(int N, DS_Type type) {
    // Both sorted and unsorted DLL require a linear search walkthrough O(N)
    algorithmic_steps += N;
}

// Router using switch-case pattern
void run_profile(DS_Type ds, int N) {
    switch (ds) {
        case UNSORTED_ARRAY:
        case SORTED_ARRAY:   simulate_array_workload(N, ds); break;
        case SLL_UNSORTED:
        case SLL_SORTED:     simulate_sll_workload(N, ds);   break;
        case DLL_UNSORTED:
        case DLL_SORTED:     simulate_dll_workload(N, ds);   break;
        default: break;
    }
}


// 3. INTEGRATED MULTIPLOT PIPE GENERATOR

void generate_multiplot_canvas(DS_Config registry[]) {
    // Connect directly to the Gnuplot executable pipe
    FILE *gnuPipe = popen("gnuplot", "w");
    
    if (gnuPipe == NULL) {
        printf("\n[!] Pipeline Error: Gnuplot could not be executed directly.\n");
        return;
    }

    // Canvas configuration settings
    fprintf(gnuPipe, "set terminal pngcairo size 1200,900 enhanced font 'Verdana,10'\n");
    fprintf(gnuPipe, "set output 'six_separate_plots.png'\n");
    
    // Initialize a 3-row, 2-column multiplot grid layout
    fprintf(gnuPipe, "set multiplot layout 3,2 title 'Worst-Case Search Complexity Across 6 Data Structures' font 'Verdana,14 bold'\n");
    
    // Shared structural graph parameters
    fprintf(gnuPipe, "set xlabel 'Input Scale (N)'\n");
    fprintf(gnuPipe, "set ylabel 'Basic Operation Steps'\n");
    fprintf(gnuPipe, "set grid\n");
    fprintf(gnuPipe, "set key left top\n");

    // Loop exactly 6 times to generate 6 individual sub-plots inside the layout
    for (int i = 0; i < TOTAL_DS_COUNT; i++) {
        // Assign a distinct sub-graph title for each configuration block
        fprintf(gnuPipe, "set title '%s performance curve'\n", registry[i].name);
        
        // Instruct Gnuplot to plot the distinct column assigned to this data structure
        fprintf(gnuPipe, "plot 'multi_ds_data.dat' using 1:%d with linespoints title '%s' lw 2 lc %d\n", 
                registry[i].data_column, registry[i].name, i + 1);
    }

    // Explicitly exit the multiplot layout rendering mode
    fprintf(gnuPipe, "unset multiplot\n");

    // Clear pipeline memory buffers
    pclose(gnuPipe);
    printf("[+] Matrix plotting sequence complete! Output saved to: six_separate_plots.png\n");
}


// 4. MAIN BENCHMARK ENGINE ENTRY

int main() {
    // Initialise structured registry profiles mapping columns explicitly
    DS_Config global_registry[TOTAL_DS_COUNT] = {
        {UNSORTED_ARRAY, "Unsorted Array", 2},
        {SORTED_ARRAY,   "Sorted Array",   3},
        {SLL_UNSORTED,   "SLL Unsorted",   4},
        {SLL_SORTED,     "SLL Sorted",     5},
        {DLL_UNSORTED,   "DLL Unsorted",   6},
        {DLL_SORTED,     "DLL Sorted",     7}
    };

    FILE* dataFile = fopen("multi_ds_data.dat", "w");
    if (!dataFile) {
        printf("Fatal: Data writing permissions missing.\n");
        return 1;
    }

    fprintf(dataFile, "# N\tUnsatArr\tSatArr\tSLLUnsat\tSLLSat\tDLLUnsat\tDLLSat\n");

    printf("[*] Compiling algorithmic scale metrics for 6 discrete layouts...\n");

    // Collect metrics for sizes N from 10 up to 1000
    for (int current_n = 10; current_n <= 1000; current_n += 50) {
        fprintf(dataFile, "%d", current_n);
        
        for (int i = 0; i < TOTAL_DS_COUNT; i++) {
            algorithmic_steps = 0; // Reset metrics metrics block
            run_profile(global_registry[i].type, current_n);
            fprintf(dataFile, "\t%lld", algorithmic_steps);
        }
        fprintf(dataFile, "\n");
    }
    
    fclose(dataFile);
    printf("[+] Profile output file written to: multi_ds_data.dat\n");

    // Invoke the integrated Gnuplot execution matrix
    generate_multiplot_canvas(global_registry);

    return 0;
}
