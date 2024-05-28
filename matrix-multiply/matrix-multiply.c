#include <stdio.h>
#include "timing.h"
#include <string.h>
#include "inputs.h"
#include "params.h"

type result[MATRIX_SIZE][MATRIX_SIZE];

void matrix_multiply(void)
{
    int i, j, k;
	type total = 0;
    memset(result, 0, sizeof(result));

    for (i = 0; i < MATRIX_SIZE; i++) {
        for (j = 0; j < MATRIX_SIZE; j++) {
            for (k = 0; k < MATRIX_SIZE; k++) {
                total += matrix1[i][k] * matrix2[k][j];
            }
			result[i][j] = total;
			total = 0;
        }
    }
}

void main(void)
{
    int i, j;
    uint64_t total_cycles;
    float total_ns;
    uint64_t start_mcycle, stop_mcycle;
    float sum_time=0;
    int sum=0;
    int it = ITERATION;


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
    
    for(i=0; i<it; i++){
      start_mcycle = get_mcycle_start();
      matrix_multiply();
      stop_mcycle = get_mcycle_stop();
	    if (i == 0)
	      continue;
      
      total_cycles = stop_mcycle - start_mcycle;
	    sum += total_cycles;
    }

    #ifdef DEBUG
      printf("\n OUTPUT MATRIX: \n");
      for (i = 0; i < MATRIX_SIZE; i++) {
        for (j = 0; j < MATRIX_SIZE; j++) {
          printf("%d ", result[i][j]);
        }
        printf("\n");
      }

      printf("\n Total iteration: %d",it);
      printf("\n Average Number of Cycles: %d", sum/it);
      printf("\n Total Number of Cycles: %d", sum);
    #endif
}
