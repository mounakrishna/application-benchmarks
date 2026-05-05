#include <stdio.h>
#include "inputs.h"
#include "encoding.h"

// Swap function (not strictly needed for insertion sort but provided for completeness)
void my_swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// Insertion Sort
void insertion_sort(int arr[], int n) {
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;

        // Move elements of arr[0..i-1] that are greater than key one position ahead
        while (j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

int main() {
    int arr[N];
    int it = (int) ITERATIONS;
    int start_cycles, end_cycles;
    int start_instr, end_instr;

    for (int i = 0; i < N; ++i)
        arr[i] = input_array[i];

  #if (HPM_ENABLE)
    start_perf();
  #endif
    write_csr(0x800, 0x27); //Enable log start
    write_csr(minstret, 0);
    write_csr(mcycle, 0);
    start_instr = read_csr(minstret);
    start_cycles = read_csr(mcycle);
    for (int i=0; i<it; i++) {
        insertion_sort(arr, N);
    }
    end_cycles = read_csr(mcycle);
    end_instr = read_csr(minstret);
    write_csr(0x800, 0x07); //Disable log start
  #if (HPM_ENABLE)
    stop_perf();
  #endif

    int pass = 1;
    for (int i = 0; i < N; ++i) {
        if (arr[i] != expected_sorted[i]) {
            printf("Mismatch at index %d: expected %d, got %d\n",
                   i, expected_sorted[i], arr[i]);
            pass = 0;
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
        printf("All insertion sort outputs match the expected sorted output!\n");
    else
        printf("Insertion sort computation failed!\n");

    return pass ? 0 : 1;
}

