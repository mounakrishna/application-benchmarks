import numpy as np
import sys

N = int(sys.argv[1])  # Number of elements; can be changed as desired
np.random.seed(0)
input_array = np.random.randint(0, 100, size=N)

# Compute expected sorted output using Python's built-in sort
expected_sorted = np.sort(input_array)

with open('bubblesort/inputs.h', 'w') as f:
    f.write('#ifndef BUBBLE_DATA_H\n#define BUBBLE_DATA_H\n\n')
    f.write(f'#define N {N}\n\n')
    f.write('int input_array[N] = {\n  ')
    f.write(', '.join(map(str, input_array)))
    f.write('\n};\n\n')
    f.write('int expected_sorted[N] = {\n  ')
    f.write(', '.join(map(str, expected_sorted)))
    f.write('\n};\n\n')
    f.write('#endif // BUBBLE_DATA_H\n')
print("Header file 'bubble_data.h' generated successfully.")
