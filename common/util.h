// See LICENSE for license details.

#ifndef __UTIL_H
#define __UTIL_H

extern void setStats(int enable);

#include <stdint.h>
#include "encoding.h"

#define static_assert(cond) switch(0) { case 0: case !!(long)(cond): ; }


#if (HPM_ENABLE)
void start_perf() {
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
}

void stop_perf() {
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
}

void print_perf() {
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
}

#endif

static int verify(int n, const volatile int* test, const int* verify)
{
  int i;
  // Unrolled for faster verification
  for (i = 0; i < n/2*2; i+=2)
  {
    int t0 = test[i], t1 = test[i+1];
    int v0 = verify[i], v1 = verify[i+1];
    if (t0 != v0) return i+1;
    if (t1 != v1) return i+2;
  }
  if (n % 2 != 0 && test[n-1] != verify[n-1])
    return n;
  return 0;
}

static int verifyDouble(int n, const volatile double* test, const double* verify)
{
  int i;
  // Unrolled for faster verification
  for (i = 0; i < n/2*2; i+=2)
  {
    double t0 = test[i], t1 = test[i+1];
    double v0 = verify[i], v1 = verify[i+1];
    int eq1 = t0 == v0, eq2 = t1 == v1;
    if (!(eq1 & eq2)) return i+1+eq1;
  }
  if (n % 2 != 0 && test[n-1] != verify[n-1])
    return n;
  return 0;
}

static void __attribute__((noinline)) barrier(int ncores)
{
  static volatile int sense;
  static volatile int count;
  static __thread int threadsense;

  __sync_synchronize();

  threadsense = !threadsense;
  if (__sync_fetch_and_add(&count, 1) == ncores-1)
  {
    count = 0;
    sense = threadsense;
  }
  else while(sense != threadsense)
    ;

  __sync_synchronize();
}

static uint64_t lfsr(uint64_t x)
{
  uint64_t bit = (x ^ (x >> 1)) & 1;
  return (x >> 1) | (bit << 62);
}

static uintptr_t insn_len(uintptr_t pc)
{
  return (*(unsigned short*)pc & 3) ? 4 : 2;
}

#ifdef __riscv
#include "encoding.h"
#endif

#define stringify_1(s) #s
#define stringify(s) stringify_1(s)
#define stats(code, iter) do { \
    unsigned long _c = -read_csr(mcycle), _i = -read_csr(minstret); \
    code; \
    _c += read_csr(mcycle), _i += read_csr(minstret); \
    if (cid == 0) \
      printf("\n%s: %ld cycles, %ld.%ld cycles/iter, %ld.%ld CPI\n", \
             stringify(code), _c, _c/iter, 10*_c/iter%10, _c/_i, 10*_c/_i%10); \
  } while(0)

#endif //__UTIL_H
