#include <stdio.h>
#include "inputs.h"
#include "encoding.h"

// Iterative binary search: returns index of key if found, else -1
int binary_search(int arr[], int n, int key) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == key)
            return mid;
        else if (arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

int main() {
    int pass = 1;
    int idx[K];
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
    for (int j = 0; j < it; j++ ) {
        for (int i = 0; i < K; ++i) {
            idx[i] = binary_search(input_array, N, search_keys[i]);
        }
    }
    end_cycles = read_csr(mcycle);
    end_instr = read_csr(minstret);
    write_csr(0x800, 0x07); //Disable log start
  #if (HPM_ENABLE)
    stop_perf();
  #endif

    for (int i = 0; i < K; i++) {
        if (idx[i] != expected_indices[i]) {
            printf("Mismatch for key %d at query %d: expected %d, got %d\n",
                   search_keys[i], i, expected_indices[i], idx[i]);
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
    
    if (pass)
        printf("All binary search results match the expected output!\n");
    else
        printf("Binary search computation failed!\n");
    return pass ? 0 : 1;
}

