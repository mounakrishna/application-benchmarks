#include <stdio.h>
#include <string.h>
#include "inputs.h"
#include "timing.h"
#include "encoding.h"

static int pixel_sad( pixel *pix1, intptr_t i_stride_pix1,  
                 pixel *pix2, intptr_t i_stride_pix2 ) 
{                                                   
    int i_sum = 0;                                  
    int lx = 16;
    int ly = 16;
    for( int y = 0; y < ly; y++ )                   
    {                                               
        for( int x = 0; x < lx; x++ )               
        {
            i_sum += abs( pix1[x] - pix2[x] );
        }                                     
        pix1 += i_stride_pix1;                
        pix2 += i_stride_pix2;                
    }                                         
    return i_sum;                             
}

int main() {
  int iterations = (int) ITERATIONS;
  int start_cycles, end_cycles;
  int start_instr, end_instr;
  int sum;

#if (HPM_ENABLE)
  start_perf();
#endif
  write_csr(0x800, 0x27); //Enable log start
  start_cycles = read_csr(mcycle);
  start_instr = read_csr(minstret);
  write_csr(minstret, 0);
  write_csr(mcycle, 0);
  for (int i=0; i<iterations; i++)
    sum = pixel_sad(pix1, 16, pix2, 16);
  end_cycles = read_csr(mcycle);
  end_instr = read_csr(minstret);
  write_csr(0x800, 0x07); //Disable log start
#if (HPM_ENABLE)
  stop_perf();
#endif
  if (sum != expected_sad) {
    printf("Output is wrong!! Expected SUM: %d, Computed SUM: %d", expected_sad, sum);
    return 0;
  }
  printf("Total cycles to execute: %d\n", (end_cycles - start_cycles));
  printf("Total instructions executed: %d\n", (end_instr - start_instr));
  printf("Total iterations: %d\n", iterations);
#if (HPM_ENABLE)
  print_perf();
#endif
}
