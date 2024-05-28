inline uint64_t get_mcycle_start() {
  uint64_t mcycle = 0;
  __asm__ volatile("csrr %0,mcycle":"=r"(mcycle));
  return mcycle;
}

inline uint64_t get_mcycle_stop(){
  uint64_t mcycle;

  __asm__ volatile("csrr %0,mcycle":"=r"(mcycle));
  return mcycle;
}
