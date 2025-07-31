#include <stdio.h>
#include "inputs.h"
#include "encoding.h"

// Perform element-wise vector addition: result = a + b
void vector_add(const int* a, const int* b, int* result, int n) {
    for (int i = 0; i < n; ++i) {
        result[i] = a[i] + b[i];
    }
}

int main() {
    int result[N];
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
    for (int i=0; i<it; i++) {
        vector_add(vec_a, vec_b, result, N);
    }
    end_cycles = read_csr(mcycle);
    end_instr = read_csr(minstret);
    write_csr(0x800, 0x07); //Disable log start
  #if (HPM_ENABLE)
    stop_perf();
  #endif

    for (int i = 0; i < N; ++i) {
        if (result[i] != expected_sum[i]) {
            printf("Mismatch at index %d: expected %d, got %d\n", i, expected_sum[i], result[i]);
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
        printf("All vector addition results match the expected output!\n");
    else
        printf("Vector addition computation failed!\n");

    return pass ? 0 : 1;
}

