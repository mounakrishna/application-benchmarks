import numpy as np
import sys

N = int(sys.argv[1])  # Length of text
np.random.seed(0)
plain_text = ''.join([chr(x) for x in np.random.randint(32, 127, size=N)])  # Printable ASCII
key = ''.join([chr(x) for x in np.random.randint(32, 127, size=8)])         # Key of length 8
# Repeat/cycle key as necessary
key_bytes = [ord(key[i % len(key)]) for i in range(N)]
plain_bytes = [ord(c) for c in plain_text]
cipher_bytes = [p ^ k for p, k in zip(plain_bytes, key_bytes)]

with open('xor_cipher/inputs.h', 'w') as f:
    f.write('#ifndef XOR_DATA_H\n#define XOR_DATA_H\n\n')
    f.write(f'#define N {N}\n#define KEYLEN {len(key)}\n\n')
    f.write('unsigned char plain_text[N] = {\n  ')
    f.write(', '.join(map(str, plain_bytes)))
    f.write('\n};\n\n')
    f.write('unsigned char key[KEYLEN] = {\n  ')
    f.write(', '.join(map(str, [ord(c) for c in key])))
    f.write('\n};\n\n')
    f.write('unsigned char expected_cipher[N] = {\n  ')
    f.write(', '.join(map(str, cipher_bytes)))
    f.write('\n};\n\n')
    f.write('#endif // XOR_DATA_H\n')
print("Header file 'inputs.h' generated successfully.")

