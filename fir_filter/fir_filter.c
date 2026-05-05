#include <stdio.h>
#include "inputs.h"
#include "encoding.h"

#define EPSILON 1e-8

// Compute absolute value without math.h
double my_fabs(double x) {
    return x >= 0 ? x : -x;
}

// Simple direct-form FIR filter
void fir_filter(const double* input, const double* coeff, int fir_len, int signal_len, double* output) {
    for (int n = 0; n < signal_len; ++n) {
        double acc = 0.0;
        for (int k = 0; k < fir_len; ++k) {
            if (n - k >= 0)
                acc += coeff[k] * input[n - k];
        }
        output[n] = acc;
    }
}

int main() {
    double result[N];
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
        fir_filter(input_signal, fir_coeff, FIR_LEN, N, result);
    }
    end_cycles = read_csr(mcycle);
    end_instr = read_csr(minstret);
    write_csr(0x800, 0x07); //Disable log start
  #if (HPM_ENABLE)
    stop_perf();
  #endif

    for (int i = 0; i < N; ++i) {
        if (my_fabs(result[i] - expected_output[i]) > EPSILON) {
            printf("Mismatch at sample %d: expected %.16f, got %.16f\n", i, expected_output[i], result[i]);
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

    if (pass) {
        printf("All FIR output values match expected output!\n");
    } else {
        printf("FIR computation failed!\n");
    }
    return pass ? 0 : 1;
}
