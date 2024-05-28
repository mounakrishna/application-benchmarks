#include <stdio.h>
#include "timing.h"
#define IMG_SIZE 10

// conv2d.c
void conv2d(int16_t *restrict mat, int16_t * restrict res,
            const int16_t * restrict coeffs,
            int W, int H, int K, uint16_t scf) {
  int R = K >> 1;
  int index = R * W;

  for(int j = R; j < H - R; j++) {
    for(int i = R; i < W - R; i++) {
      int index2 = index - R * W;
      int c = 0;
      int val = 0;
      for(int y = -R; y <= R; ++y) {
        val += coeffs[c++] * mat[index2 + i - 2];
        val += coeffs[c++] * mat[index2 + i -1];
        val += coeffs[c++] * mat[index2 + i];
        val += coeffs[c++] * mat[index2 + i + 1];
        val += coeffs[c++] * mat[index2 + i + 2];
        index2 += W;
      }
      res[index+i] = val >> scf;
    }
    index += W;
  }
}

// conv2d_test.c
static int16_t coeffs[] = {
  1, 4, 6, 4, 1,
  4,16,24,16, 4,
  6,24,36,24, 6,
  4,16,24,16, 4,
  1, 4, 6, 4, 1 };

static const int16_t check[IMG_SIZE * IMG_SIZE] = {
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0, 22, 23, 24, 25, 26, 27,  0,  0,
  0,  0, 32, 33, 34, 35, 36, 37,  0,  0,
  0,  0, 42, 43, 44, 45, 46, 47,  0,  0,
  0,  0, 52, 53, 54, 55, 56, 57,  0,  0,
  0,  0, 62, 63, 64, 65, 66, 67,  0,  0,
  0,  0, 72, 73, 74, 75, 76, 77,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
};

static int16_t img_in[IMG_SIZE * IMG_SIZE];
static int16_t img_out[IMG_SIZE * IMG_SIZE];

void test_setup() {
  for (int i = 0; i != IMG_SIZE*IMG_SIZE; i++)
    img_in[i] = i;
}

void test_clear() {
  memset(img_out, 0, IMG_SIZE*IMG_SIZE);
}

void test_run() {
  conv2d(img_in, img_out, coeffs, IMG_SIZE, IMG_SIZE, 5, 8);
}

int test_check() {
  return 0 == memcmp(img_out, check, IMG_SIZE*IMG_SIZE);
}

// main.c
int main() {
  uint64_t total_cycles;
  float total_ns;
  uint64_t start_mcycle, stop_mcycle;
  float sum_time=0;
  int sum=0;

  test_setup();
  test_clear();
  start_mcycle = get_mcycle_start();
  test_run();
  stop_mcycle = get_mcycle_stop();

  total_cycles = stop_mcycle - start_mcycle;
  sum += total_cycles;

  int check = test_check();

  if (check == 1)
    printf("== test:-> success, nr. of errors: %d, Total Number of Cycles: %d",0,total_cycles);
  else
    printf("== test:-> fail, nr. of errors: %d\n",1);

  return 0;
}
