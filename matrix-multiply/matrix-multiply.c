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
   
    #ifdef HPM_ENABLE
	    write_csr(mhpmevent3, EVENT_MISPREDICTION     );
	    write_csr(mhpmevent4, EVENT_EXCEPTIONS        );
	    //write_csr(mhpmevent4, EVENT_MUL_BRANCH_HAZARD );
	    write_csr(mhpmevent5, EVENT_CSROPS            );
      //write_csr(mhpmevent5, EVENT_MUL_MEM_HAZARD    );
	    write_csr(mhpmevent6, EVENT_JUMPS             );
	    write_csr(mhpmevent7, EVENT_BRANCHES          );
	    write_csr(mhpmevent8, EVENT_FLOATS            );
	    write_csr(mhpmevent9, EVENT_MULDIV            );
	    write_csr(mhpmevent10,EVENT_RAWSTALLS         );
	    write_csr(mhpmevent11,EVENT_EXESTALLS         );
	    write_csr(mhpmevent12,EVENT_INSTR_QUEUE_FULL  );
	    write_csr(mhpmevent13,EVENT_INSTR_QUEUE_EMPTY );
	    write_csr(mhpmevent14,EVENT_DUAL_ISSUED       );
	    //write_csr(mhpmevent15,EVENT_ISB3_ISB4_FULL    );
      write_csr(mhpmevent15,EVENT_MUL_FLOAT_HAZARD  );
	    //write_csr(mhpmevent16,EVENT_ISB3_ISB4_EMPTY   );
      write_csr(mhpmevent16,EVENT_MUL_MUL_HAZARD    );
	    //write_csr(mhpmevent17,EVENT_ISB4_ISB5_FULL    );
      write_csr(mhpmevent17,EVENT_MEM_MEM_HAZARD    );
	    //write_csr(mhpmevent18,EVENT_ISB4_ISB5_EMPTY   );
      write_csr(mhpmevent18,EVENT_MEM_BRANCH_HAZARD );
      //write_csr(mhpmevent19,EVENT_ICACHE_ACCESS     );
      write_csr(mhpmevent19,EVENT_MEM_FLOAT_HAZARD  );
      //write_csr(mhpmevent20,EVENT_ICACHE_MISS       );
      write_csr(mhpmevent20,EVENT_FLOAT_BRANCH_HAZARD);
      //write_csr(mhpmevent21,EVENT_DCACHE_READ_ACCESS);
      write_csr(mhpmevent21,EVENT_FLOAT_FLOAT_HAZARD);
      //write_csr(mhpmevent22,EVENT_DCACHE_READ_MISS  );
      write_csr(mhpmevent22,EVENT_BRANCH_BRANCH_HAZARD);
      //write_csr(mhpmevent23,EVENT_DCACHE_WRITE_ACCESS);
      write_csr(mhpmevent23,EVENT_MUL_BRANCH_HAZARD );
      //write_csr(mhpmevent24,EVENT_DCACHE_WRITE_MISS );
      write_csr(mhpmevent25,EVENT_MUL_MEM_HAZARD    );
      write_csr(mhpmevent25,EVENT_RAW_HAZARD        );
      write_csr(mhpmevent26,EVENT_ONE_INSTR        );
      write_csr(mhpmevent27,EVENT_EXEFLUSH          );
      write_csr(mhpmevent28,EVENT_WBFLUSH           );
      write_csr(mhpmevent29,EVENT_ST3_NOT_FIRING    );
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

    #endif
    printf("\n Total iteration: %d",it);
    printf("\n Average Number of Cycles: %d", sum/it);
    printf("\n Total Number of Cycles: %d\n", sum);
#if (HPM_ENABLE)
	write_csr(mhpmevent3,0);
	write_csr(mhpmevent4,0);
	write_csr(mhpmevent5,0);
	write_csr(mhpmevent6,0);
	write_csr(mhpmevent7,0);
	write_csr(mhpmevent8,0);
	write_csr(mhpmevent9,0);
	write_csr(mhpmevent10,0);
	write_csr(mhpmevent11,0);
	write_csr(mhpmevent12,0);
	write_csr(mhpmevent13,0);
	write_csr(mhpmevent14,0);
	write_csr(mhpmevent15,0);
	write_csr(mhpmevent16,0);
	write_csr(mhpmevent17,0);
	write_csr(mhpmevent18,0);
	write_csr(mhpmevent19,0);
	write_csr(mhpmevent20,0);
	write_csr(mhpmevent21,0);
	write_csr(mhpmevent22,0);
	write_csr(mhpmevent23,0);
	write_csr(mhpmevent24,0);
	write_csr(mhpmevent25,0);
	write_csr(mhpmevent26,0);
	write_csr(mhpmevent27,0);
	write_csr(mhpmevent28,0);
	write_csr(mhpmevent29,0);
	//write_csr(mhpmevent30,0);
	//write_csr(mhpmevent31,0);
	printf("misprediction = %d \n",read_csr(mhpmcounter3));
	printf("exceptions = %d \n",read_csr(mhpmcounter4));
	printf("csrops= %d \n",read_csr(mhpmcounter5));
	printf("jumps= %d \n",read_csr(mhpmcounter6));
	printf("branches= %d \n",read_csr(mhpmcounter7));
	printf("floats= %d \n",read_csr(mhpmcounter8));
	printf("muldiv= %d \n",read_csr(mhpmcounter9));
	printf("rawstalls= %d \n",read_csr(mhpmcounter10));
	printf("exetalls= %d \n",read_csr(mhpmcounter11));
  printf("instr_queue_full= %d\n", read_csr(mhpmcounter12));
  printf("instr_queue_empty= %d\n", read_csr(mhpmcounter13));
  printf("dual_issued= %d\n", read_csr(mhpmcounter14));
  //printf("isb3_isb4_full= %d\n", read_csr(mhpmcounter15));
  //printf("isb3_isb4_empty= %d\n", read_csr(mhpmcounter16));
  //printf("isb4_isb5_full= %d\n", read_csr(mhpmcounter17));
  //printf("isb4_isb5_empty= %d\n", read_csr(mhpmcounter18));
  //printf("icache_access= %d\n", read_csr(mhpmcounter19));
  //printf("icache_miss= %d\n", read_csr(mhpmcounter20));
  //printf("dcache_read_access= %d\n", read_csr(mhpmcounter21));
  //printf("dcache_read_miss= %d\n", read_csr(mhpmcounter22));
  //printf("dcache_write_access= %d\n", read_csr(mhpmcounter23));
  //printf("dcache_write_miss= %d\n", read_csr(mhpmcounter24));
  printf("mul_float_hazard= %d\n", read_csr(mhpmcounter15));
  printf("mul_mul_hazard= %d\n", read_csr(mhpmcounter16));
  printf("mem_mem_hazard= %d\n", read_csr(mhpmcounter17));
  printf("mem_branch_hazard= %d\n", read_csr(mhpmcounter18));
  printf("mem_float_hazard= %d\n", read_csr(mhpmcounter19));
  printf("float_branch_hazard= %d\n", read_csr(mhpmcounter20));
  printf("float_float_hazard= %d\n", read_csr(mhpmcounter21));
  printf("branch_branch_hazard= %d\n", read_csr(mhpmcounter22));
  printf("mul_branch_hazard= %d\n", read_csr(mhpmcounter23));
  printf("mul_mem_hazard= %d\n", read_csr(mhpmcounter24));
  printf("raw_hazard= %d\n", read_csr(mhpmcounter25));
  printf("Only One instruction present in queue = %d\n", read_csr(mhpmcounter26));
  printf("Number of Execute flushes = %d\n", read_csr(mhpmcounter27));
  printf("Number of WriteBack flushes = %d\n", read_csr(mhpmcounter28));
  printf("Number of times Stage3 is not firing = %d\n", read_csr(mhpmcounter29));
#endif
}
