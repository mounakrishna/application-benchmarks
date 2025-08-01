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
  printf("Total iterations: %d\n", iterations);
#if (HPM_ENABLE)
  print_perf();
#endif
}

