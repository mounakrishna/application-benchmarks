#include <stdio.h>
#include "encoding.h"

#define N 100
#define EPSILON 1e-8

#include "inputs.h"

void autocorrelation(const double* x, int n, double* out) {
    double sumsq = 0.0;
    for (int i = 0; i < n; ++i)
        sumsq += x[i] * x[i];

    for (int lag = 0; lag < n; ++lag) {
        double sum = 0.0;
        for (int i = 0; i < n - lag; ++i)
            sum += x[i] * x[i + lag];
        out[lag] = sum / sumsq;
    }
}

// Inline absolute value for doubles, since math.h is not used
double my_fabs(double x) {
    return x >= 0 ? x : -x;
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
      autocorrelation(input_signal, N, result);
    }
    end_cycles = read_csr(mcycle);
    end_instr = read_csr(minstret);
    write_csr(0x800, 0x07); //Disable log start
  #if (HPM_ENABLE)
    stop_perf();
  #endif

    for (int i = 0; i < N; ++i) {
        if (my_fabs(result[i] - expected_output[i]) > EPSILON) {
            printf("Mismatch at lag %d: expected %.16f, got %.16f\n",
                   i, expected_output[i], result[i]);
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
        printf("All autocorrelation values match expected output!\n");
    } else {
        printf("Autocorrelation computation failed!\n");
    }

    return pass ? 0 : 1;
}
