import numpy as np
import sys

N = int(sys.argv[1])  # Vector length
np.random.seed(0)

# Generate two random input vectors
vec_a = np.random.randint(0, 100, size=N)
vec_b = np.random.randint(0, 100, size=N)

# Compute expected element-wise sum
expected_sum = vec_a + vec_b

# Write to a C header file
with open('vec_add/inputs.h', 'w') as f:
    f.write('#ifndef VECTOR_ADD_DATA_H\n#define VECTOR_ADD_DATA_H\n\n')
    f.write(f'#define N {N}\n\n')
    
    f.write('int vec_a[N] = {\n  ')
    f.write(', '.join(map(str, vec_a)))
    f.write('\n};\n\n')
    
    f.write('int vec_b[N] = {\n  ')
    f.write(', '.join(map(str, vec_b)))
    f.write('\n};\n\n')
    
    f.write('int expected_sum[N] = {\n  ')
    f.write(', '.join(map(str, expected_sum)))
    f.write('\n};\n\n')

    f.write('#endif // VECTOR_ADD_DATA_H\n')

print("Header file for vec_add generated successfully.")

