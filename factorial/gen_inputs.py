import numpy as np
import math

N = 12  # Up to 12 to keep all results in 32 bits (12! = 479001600)
inputs = np.arange(0, N + 1)
outputs = [math.factorial(x) for x in inputs]

with open('factorial/inputs.h', 'w') as f:
    f.write('#ifndef FACTORIAL_DATA_H\n#define FACTORIAL_DATA_H\n\n')
    f.write(f'#define N_FACT {N+1}\n\n')
    f.write('int factorial_inputs[N_FACT] = {\n  ')
    f.write(', '.join(map(str, inputs)))
    f.write('\n};\n\n')
    f.write('int expected_outputs[N_FACT] = {\n  ')
    f.write(', '.join(map(str, outputs)))
    f.write('\n};\n\n')
    f.write('#endif // FACTORIAL_DATA_H\n')

print("Header file 'factorial_data.h' generated successfully.")

