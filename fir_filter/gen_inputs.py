import numpy as np
import sys

N = int(sys.argv[1])             # Signal length
FIR_LEN = int(sys.argv[2])        # Number of FIR taps (coefficients)
np.random.seed(0)

input_signal = np.random.rand(N)
fir_coeff = np.random.rand(FIR_LEN) - 0.5  # random FIR, values in [-0.5, 0.5]

# Compute FIR output (same as np.convolve with mode='full', but truncate to length N)
expected_output = np.convolve(input_signal, fir_coeff, mode='full')[:N]

with open('fir_filter/inputs.h', 'w') as f:
    f.write('#ifndef FIR_DATA_H\n#define FIR_DATA_H\n\n')
    f.write(f'#define N {N}\n#define FIR_LEN {FIR_LEN}\n\n')
    f.write('double input_signal[N] = {\n  ')
    f.write(',\n  '.join(map(str, input_signal)))
    f.write('\n};\n\n')
    f.write('double fir_coeff[FIR_LEN] = {\n  ')
    f.write(',\n  '.join(map(str, fir_coeff)))
    f.write('\n};\n\n')
    f.write('double expected_output[N] = {\n  ')
    f.write(',\n  '.join(map(str, expected_output)))
    f.write('\n};\n\n')
    f.write('#endif // FIR_DATA_H\n')

print("Header file 'fir_data.h' generated successfully.")
