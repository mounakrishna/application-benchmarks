#include <stdio.h>
#include "inputs.h"
#include "encoding.h"

// XOR encryption/decryption (same for both)
void xor_cipher(const unsigned char* in, unsigned char* out, const unsigned char* key, int text_len, int key_len) {
    int j=0;
    for (int i = 0; i < text_len; ++i) {
        out[i] = in[i] ^ key[j];

        if (j==(KEYLEN-1))
          j=0;
        else
          j+=1;
    }
}

int main() {
    unsigned char cipher[N], recover[N];
    int pass = 1;
    int it = (int) ITERATIONS;
    int start_cycles, end_cycles;
    int start_instr, end_instr;

    printf("Encrypting Data \n");
  #if (HPM_ENABLE)
    start_perf();
  #endif
    write_csr(0x800, 0x27); //Enable log start
    write_csr(minstret, 0);
    write_csr(mcycle, 0);
    start_instr = read_csr(minstret);
    start_cycles = read_csr(mcycle);
    // Encrypt
    for (int i=0; i<it; i++) {
        xor_cipher(plain_text, cipher, key, N, KEYLEN);
    }
    end_cycles = read_csr(mcycle);
    end_instr = read_csr(minstret);
    write_csr(0x800, 0x07); //Disable log start
  #if (HPM_ENABLE)
    stop_perf();
  #endif
    // Check encryption result
    for (int i = 0; i < N; ++i) {
        if (cipher[i] != expected_cipher[i]) {
            printf("Encryption mismatch at position %d: expected %u, got %u\n", i, expected_cipher[i], cipher[i]);
            pass = 0;
            return 1;
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

    printf("Decrypting Data \n");
  #if (HPM_ENABLE)
    start_perf();
  #endif
    write_csr(0x800, 0x27); //Enable log start
    write_csr(minstret, 0);
    write_csr(mcycle, 0);
    start_cycles = read_csr(mcycle);
    start_instr = read_csr(minstret);
    // Decrypt
    for (int i=0; i<it; i++) {
      xor_cipher(cipher, recover, key, N, KEYLEN);
    }
    end_cycles = read_csr(mcycle);
    end_instr = read_csr(minstret);
    write_csr(0x800, 0x07); //Disable log start
  #if (HPM_ENABLE)
    stop_perf();
  #endif
    // Check if we get back the original text
    for (int i = 0; i < N; ++i) {
        if (recover[i] != plain_text[i]) {
            printf("Decryption mismatch at position %d: expected %u, got %u\n", i, plain_text[i], recover[i]);
            pass = 0;
            return 1;
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

    if (pass)
        printf("All XOR cipher outputs match the expected outputs!\n");
    else
        printf("XOR cipher test failed!\n");
    return pass ? 0 : 1;
}

