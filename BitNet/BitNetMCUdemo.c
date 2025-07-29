/* Using BitNeuMCU for inference of 16x16 MNIST images on a CH32V003 */

#include "timing.h"
#include "encoding.h"
#include <stdint.h>
#include <stdio.h>

// Declare processfclayer an SRAM based function for speedup
void processfclayer(int8_t *,  const uint32_t *, int32_t, uint32_t, uint32_t, int32_t *) __attribute__((section(".srodata"))) __attribute__((used));

#include "BitNetMCU_inference.c"
// #include "BitNetMCU_model_1k.h"
#include "BitNetMCU_model_12k.h"
// #include "BitNetMCU_model_12k_FP130.h"

const int8_t input_data_0[256] = {-22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, 11.0, 64.0, 30.0, 6.0, -14.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, 28.0, 124.0, 127.0, 115.0, 66.0, -3.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -12.0, 18.0, 58.0, 97.0, 124.0, 70.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -16.0, 47.0, 100.0, -11.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -21.0, 44.0, 104.0, -11.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -16.0, 68.0, 106.0, -12.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -13.0, 77.0, 99.0, -18.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -13.0, 77.0, 96.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -13.0, 77.0, 96.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -13.0, 77.0, 96.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -17.0, 62.0, 97.0, -20.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, 18.0, 71.0, -14.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -20.0, -16.0, -21.0, -22.0, -22.0, -22.0, -22.0, -22.0};
//const uint32_t label_0 = 7;
const int8_t input_data_1[256] = {-20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -4.0, 69.0, 6.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, 5.0, 106.0, 42.0, -18.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, 28.0, 119.0, 50.0, -17.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -14.0, 64.0, 125.0, 19.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, 3.0, 99.0, 121.0, 13.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -19.0, 33.0, 120.0, 100.0, -7.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -16.0, 71.0, 126.0, 65.0, -17.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, 6.0, 106.0, 112.0, 13.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, 47.0, 125.0, 100.0, -3.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, 54.0, 127.0, 68.0, -19.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, 53.0, 119.0, 43.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, 16.0, 59.0, -3.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0};
//const uint32_t label_1 = 1;
const int8_t input_data_2[256] = {-21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -16.0, 11.0, 49.0, 48.0, 0.0, -20.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -20.0, -5.0, 41.0, 80.0, 62.0, 56.0, 70.0, 0.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -18.0, 10.0, 76.0, 58.0, 3.0, -18.0, -14.0, 70.0, 24.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -19.0, 28.0, 94.0, 29.0, -15.0, -21.0, -21.0, 1.0, 99.0, 47.0, -20.0, -21.0, -21.0, -21.0, -21.0, -21.0, 7.0, 87.0, 29.0, -19.0, -21.0, -20.0, -9.0, 65.0, 90.0, 7.0, -21.0, -21.0, -21.0, -21.0, -21.0, -19.0, 55.0, 67.0, -14.0, -21.0, -20.0, -4.0, 77.0, 118.0, 30.0, -19.0, -21.0, -21.0, -21.0, -21.0, -21.0, -17.0, 68.0, 33.0, -12.0, -0.0, 29.0, 69.0, 127.0, 72.0, -12.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -18.0, 55.0, 91.0, 84.0, 75.0, 38.0, 51.0, 111.0, 8.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -11.0, 16.0, 14.0, -8.0, -13.0, 62.0, 65.0, -18.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -3.0, 84.0, 18.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, 14.0, 68.0, -13.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, 8.0, 39.0, -17.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -20.0, -18.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0};
//const uint32_t label_2 = 9;
const int8_t input_data_3[256] = {-20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -13.0, -15.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -6.0, 41.0, 78.0, 38.0, -18.0, -20.0, -20.0, -20.0, -20.0, -17.0, -17.0, -20.0, -20.0, -20.0, -20.0, -11.0, 67.0, 109.0, 63.0, 6.0, -20.0, -20.0, -20.0, -20.0, -8.0, 48.0, 50.0, -8.0, -20.0, -20.0, -20.0, 2.0, 108.0, 65.0, -14.0, -20.0, -20.0, -20.0, -20.0, -12.0, 59.0, 114.0, 89.0, 4.0, -20.0, -20.0, -20.0, 10.0, 114.0, 27.0, -20.0, -20.0, -20.0, -20.0, -20.0, 36.0, 122.0, 65.0, -14.0, -20.0, -20.0, -20.0, -20.0, -2.0, 96.0, 55.0, -13.0, -20.0, -20.0, -20.0, -12.0, 89.0, 114.0, 16.0, -20.0, -20.0, -20.0, -20.0, -20.0, -17.0, 43.0, 100.0, 46.0, -5.0, -15.0, -18.0, 6.0, 115.0, 84.0, -9.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -14.0, 45.0, 115.0, 100.0, 78.0, 50.0, 66.0, 127.0, 53.0, -17.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -13.0, 28.0, 76.0, 91.0, 104.0, 127.0, 122.0, 28.0, -18.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -19.0, -16.0, -14.0, -1.0, 71.0, 114.0, 8.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, 19.0, 112.0, 39.0, -13.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -11.0, 70.0, 89.0, 19.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -18.0, -6.0, -18.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0};
//const uint32_t label_3 = 4;

struct output {
  int cycles;
  int instructions;
};

struct output BitMnistInference(const int8_t *input, const uint8_t label, const uint8_t sample) {
    int32_t layer_out[MAX_N_ACTIVATIONS];
    int8_t layer_in[MAX_N_ACTIVATIONS];
	  int32_t prediction;
	  int startticks, endticks;
	  int startinstr, endinstr;

    #if (HPM_ENABLE)
      start_perf();
    #endif
	//startticks = SysTick->CNT;
    startinstr = read_csr(minstret);
    startticks = get_mcycle_start();
    processfclayer((int8_t*)input, L1_weights, L1_bitperweight, L1_incoming_weights, L1_outgoing_weights, layer_out);
    ReLUNorm(layer_out, layer_in, L1_outgoing_weights);

    processfclayer(layer_in, L2_weights, L2_bitperweight, L2_incoming_weights,  L2_outgoing_weights, layer_out);
    ReLUNorm(layer_out, layer_in, L2_outgoing_weights);

    processfclayer(layer_in, L3_weights, L3_bitperweight, L3_incoming_weights,  L3_outgoing_weights, layer_out);
    prediction=ReLUNorm(layer_out, layer_in, L3_outgoing_weights);

#if NUM_LAYERS == 4
    processfclayer(layer_in, L4_weights, L4_bitperweight, L4_incoming_weights,  L4_outgoing_weights, layer_out);
    prediction=ReLUNorm(layer_out, layer_in, L4_outgoing_weights);
#endif

	//endticks = SysTick->CNT;
    endticks = get_mcycle_stop();
    endinstr = read_csr(minstret);
    #if (HPM_ENABLE)
      stop_perf();
    #endif

  struct output o;
  o.cycles = (endticks - startticks);
  o.instructions = endinstr-startinstr;
	printf( "Inference of Sample %d\tPrediction: %ld\tLabel: %d\tTiming: %lu clock cycles %lu instructions \n", sample, prediction, label, o.cycles, o.instructions);	

  return o;
}

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

int main()
{
	//SystemInit();
//	SysTick->CTLR = 5;  // Use HCLK as time base -> configured in funconfig.h
//
  
  int iterations = (int) ITERATIONS;
  //int cycles[4] = {0, 0, 0, 0};
  struct output out[4] = {{0,0},{0,0},{0,0},{0,0}};
  struct output tmp;
  int total_cycles;
  int start_minstret, stop_minstret, total_instr;

	printf("Starting MNIST inference...\n");
  start_minstret = read_csr(minstret);
  //start_mcycle = get_mcycle_start();
  write_csr(0x800, 0x27); //Enable log start
  write_csr(mcycle, 0);
  write_csr(minstret, 0);
	for (int i=0; i<iterations; i++)
	{
		tmp = BitMnistInference(input_data_0, 7,1);
    out[0].cycles += tmp.cycles;
    out[0].instructions += tmp.instructions;
	}
	for (int i=0; i<iterations; i++)
	{
		tmp = BitMnistInference(input_data_1, 1,2);	
    out[1].cycles += tmp.cycles;
    out[1].instructions += tmp.instructions;
  }
	for (int i=0; i<iterations; i++)
	{
		tmp = BitMnistInference(input_data_2, 9,3);	
    out[2].cycles += tmp.cycles;
    out[2].instructions += tmp.instructions;
  }
	for (int i=0; i<iterations; i++)
	{
		tmp = BitMnistInference(input_data_3, 4,4);	
    out[3].cycles += tmp.cycles;
    out[3].instructions += tmp.instructions;
  }
  //stop_mcycle = get_mcycle_stop();
  stop_minstret = read_csr(minstret);
  write_csr(0x800, 0x07); //Disable log start
  total_cycles = out[0].cycles + out[1].cycles + out[2].cycles + out[3].cycles;
  total_instr = out[0].instructions + out[1].instructions + out[2].instructions + out[3].instructions;
  //total_instr = stop_minstret - start_minstret;
  printf("Sample 1 instructions: %d time taken: %d label: 7\n", out[0].instructions/iterations, out[0].cycles/iterations);
  printf("Sample 2 instructions: %d time taken: %d label: 1\n", out[1].instructions/iterations, out[1].cycles/iterations);
  printf("Sample 3 instructions: %d time taken: %d label: 9\n", out[2].instructions/iterations, out[2].cycles/iterations);
  printf("Sample 4 instructions: %d time taken: %d label: 4\n", out[3].instructions/iterations, out[3].cycles/iterations);
  printf("Total Cycles to execute: %d\n", total_cycles);
  printf("Total instructions executed: %d\n", total_instr);
#if (HPM_ENABLE)
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

