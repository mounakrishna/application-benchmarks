#include <stdio.h>
#include "inputs.h"
#include "encoding.h"

int factorial(int n) {
    int fact = 1;
    for (int i = 1; i <= n; ++i)
        fact *= i;
    return fact;
}

int main() {
    int pass = 1;
    int it = (int) ITERATIONS;
    int start_cycles, end_cycles;
    int start_instr, end_instr;
    int got[N_FACT];

  #if (HPM_ENABLE)
    start_perf();
  #endif
    write_csr(0x800, 0x27); //Enable log start
    write_csr(minstret, 0);
    write_csr(mcycle, 0);
    start_instr = read_csr(minstret);
    start_cycles = read_csr(mcycle);
    for (int j = 0; j < it; j++) {
        for (int i = 0; i < N_FACT; ++i) {
            got[i] = factorial(factorial_inputs[i]);
        }
    }
    end_cycles = read_csr(mcycle);
    end_instr = read_csr(minstret);
    write_csr(0x800, 0x07); //Disable log start
  #if (HPM_ENABLE)
    stop_perf();
  #endif

    for (int i = 0; i < N_FACT; i++) {
        if (got[i] != expected_outputs[i]) {
            printf("Mismatch at input %d: expected %d, got %d\n", factorial_inputs[i], expected_outputs[i], got[i]);
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
        printf("All factorial outputs match expected outputs!\n");
    else
        printf("Factorial computation failed!\n");
    return pass ? 0 : 1;
}

