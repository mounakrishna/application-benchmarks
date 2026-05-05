#include <stdio.h>
#include "inputs.h"
#include "encoding.h"

#define ABS(x) ((x) >= 0 ? (x) : -(x))
#define EPSILON 1e-8

// Sorts arr[] of length n, returns median (odd n assumed)
unsigned char median(unsigned char* arr, int n) {
    for (int i = 0; i < n-1; ++i) {
        for (int j = i+1; j < n; ++j) {
            if (arr[j] < arr[i]) {
                unsigned char t = arr[i]; arr[i] = arr[j]; arr[j] = t;
            }
        }
    }
    return arr[n/2];
}

// 2D Median filter with zero padding at borders
void median_filter2d(const unsigned char in[ROWS][COLS], unsigned char out[ROWS][COLS], int ksz) {
    int pad = ksz / 2;
    unsigned char window[49]; // works for ksz up to 7

    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            int idx = 0;
            for (int u = -pad; u <= pad; ++u) {
                for (int v = -pad; v <= pad; ++v) {
                    int x = i + u, y = j + v;
                    if (x >= 0 && x < ROWS && y >= 0 && y < COLS)
                        window[idx++] = in[x][y];
                    else
                        window[idx++] = 0; // zero-padding
                }
            }
            out[i][j] = median(window, ksz*ksz);
        }
    }
}

int main() {
    unsigned char result[ROWS][COLS];
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
        median_filter2d(input_image, result, KERNEL_SIZE);
    }
    end_cycles = read_csr(mcycle);
    end_instr = read_csr(minstret);
    write_csr(0x800, 0x07); //Disable log start
  #if (HPM_ENABLE)
    stop_perf();
  #endif

    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (ABS((int)result[i][j] - (int)expected_output[i][j]) > 0) {
                printf("Mismatch at (%d, %d): expected %d, got %d\n", i, j, expected_output[i][j], result[i][j]);
                pass = 0;
            }
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
    
    if (pass) printf("All median-filtered values match expected output!\n");
    else printf("Median filter computation failed!\n");
    return pass ? 0 : 1;
}

