#include <stdio.h>
#include "inputs.h"
#include "encoding.h"

// Swap function without math.h
void my_swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// Bubble Sort
void bubble_sort(int arr[], int n) {
    for (int i = 0; i < n-1; ++i) {
        int swapped = 0;
        for (int j = 0; j < n-i-1; ++j) {
            if (arr[j] > arr[j+1]) {
                my_swap(&arr[j], &arr[j+1]);
                swapped = 1;
            }
        }
        if (!swapped) break;
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
        bubble_sort(arr, N);
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
            printf("Mismatch at index %d: expected %d, got %d\n", i, expected_sorted[i], arr[i]);
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
        printf("All bubble sort outputs match the expected output!\n");
    else
        printf("Bubble sort computation failed!\n");

    return pass ? 0 : 1;
}

