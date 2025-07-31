#include <stdio.h>
#include <string.h>
#include "inputs.h"
#include "params.h"
#include "timing.h"
#include "encoding.h"

type result[MATRIX_SIZE][MATRIX_SIZE];

void matrix_multiply(void)
{
    int i, j, k;
	  type total = 0;
    //memset(result, 0, sizeof(result));

    for (i = 0; i < MATRIX_SIZE; i++) {
        for (j = 0; j < MATRIX_SIZE; j++) {
            for (k = 0; k < MATRIX_SIZE; k++) {
                //printf("[%d][%d][%d] matrix1: %d, matrix2: %d\n", i, j, k, matrix1[i][k], matrix2[k][j]);
                total += matrix1[i][k] * matrix2[k][j];
            }
			result[i][j] = total;
			total = 0;
        }
    }
}

int main()
{
    int i, j;
    uint64_t total_cycles = 0;
    uint64_t total_instructions = 0;
    float total_ns;
    uint64_t start_mcycle, stop_mcycle;
    uint64_t start_minstret, stop_minstret;
    float sum_time=0;
    int it = ITERATIONS;


    #ifdef DEBUG    
      printf("\n ...Hello World again..."); 
      printf("\n INPUT MATRIX A: \n");

      for(i=0; i<MATRIX_SIZE; i++){
        for(j=0; j<MATRIX_SIZE; j++){
          printf("%d ", matrix1[i][j]);
        }
	    printf("\n");
      }
    
      printf("\n INPUT MATRIX B: \n");

      for(i=0; i<MATRIX_SIZE; i++){
        for(j=0; j<MATRIX_SIZE; j++){
          printf("%d ", matrix2[i][j]);
        }
	      printf("\n");
      }
      printf("\n Lets check the output of the 4x4 Matrix Multiplication...");
      printf("\n GOING TO CALL MATRIX-MULTIPLY");
    #endif
   
    #ifdef HPM_ENABLE
      start_perf();
    #endif
    write_csr(0x800, 0x27); //Enable log start
    for(i=0; i<it; i++){
      start_minstret = read_csr(minstret);
      start_mcycle = get_mcycle_start();
      matrix_multiply();
      stop_mcycle = get_mcycle_stop();
      stop_minstret = read_csr(minstret);
	    if (i == 0)
	      continue;
      
      total_cycles += stop_mcycle - start_mcycle;
      total_instructions += stop_minstret - start_minstret;
    }
    write_csr(0x800, 0x07); //Disable log start
    #ifdef HPM_ENABLE
      stop_perf();
    #endif

    #ifdef DEBUG
      printf("\n OUTPUT MATRIX: \n");
      for (i = 0; i < MATRIX_SIZE; i++) {
        for (j = 0; j < MATRIX_SIZE; j++) {
          printf("%d ", result[i][j]);
        }
        printf("\n");
      }

    #endif

    for (i = 0; i < MATRIX_SIZE; i++) {
      for (j = 0; j < MATRIX_SIZE; j++) {
        if (result[i][j] != expected_result_matrix[i][j]) {
          printf("Outputs do not match at index [%d][%d]\n", i, j);
          printf("Expected value: %d Computed value: %d", expected_result_matrix[i][j], result[i][j]);
          return 0;
        }
      }
    }
    printf("\nTotal iteration: %d",it);
    printf("\nMatrix Size: %d", MATRIX_SIZE);
    printf("\nTotal Number of Cycles: %d", total_cycles);
    printf("\nTotal Number of Instructions: %d\n", total_instructions);
    #if (HPM_ENABLE)
      print_perf();
    #endif

    return 0;
}
