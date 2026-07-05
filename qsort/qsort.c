#include <stddef.h>
#include "inputs.h"
#include "encoding.h"

// In-place swap helper
void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// Partition function for QuickSort
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; 
    int i = (low - 1); 

    for (int j = low; j <= high - 1; j++) {
        // This linear scan across elements induces D$ misses
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// QuickSort function
void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        
        // Recursive calls stress the stack frame in memory
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

// Volatile variable easily visible in RTL simulations / memory dumps
volatile int test_status = 0; // 0 = Running/Untested, 1 = Pass, 2 = Fail

int main() {
    int pass = 1;
    int it = (int) ITERATIONS;
    int start_cycles, end_cycles;
    int start_instr, end_instr;
 
  #if (HPM_ENABLE)
    start_perf();
  #endif
    write_csr(0x800, 0x27); //Enable log start
    write_csr(minstret, 0);
    write_csr(mcycle, 0);
    start_instr = read_csr(minstret);
    start_cycles = read_csr(mcycle);

    // Run the sort
    for (int i = 0; i<it; i++) {
      quick_sort(input_array, 0, ARRAY_SIZE - 1);
    }

    end_cycles = read_csr(mcycle);
    end_instr = read_csr(minstret);
    write_csr(0x800, 0x07); //Disable log start
  #if (HPM_ENABLE)
    stop_perf();
  #endif


    // Validate against the Python reference data
    int match = 1;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (input_array[i] != reference_array[i]) {
            match = 0;
            printf("Mismatch\n");
            pass = 0;
            return 1;
        }
    }

    if (pass) {
        printf("Total cycles to execute: %d\n", (end_cycles - start_cycles));
        printf("Total instructions executed: %d\n", (end_instr - start_instr));
        printf("Total iterations: %d\n", it);
      #if (HPM_ENABLE)
        print_perf();
      #endif
    }
    printf("\n\n");
    printf("All binary search results match the expected output!\n");

    return 0;
}
