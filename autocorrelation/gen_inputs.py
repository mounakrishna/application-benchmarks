import numpy as np
import sys

N = int(sys.argv[1])
np.random.seed(0)
input_signal = np.random.rand(N)

# Compute the normalized autocorrelation for non-negative lags
expected_output = np.correlate(input_signal, input_signal, mode='full') / np.sum(input_signal**2)
expected_output = expected_output[len(input_signal)-1:]

# Write arrays to a C header file
with open('autocorrelation/inputs.h', 'w') as f:
    f.write('#ifndef AUTOCORR_DATA_H\n#define AUTOCORR_DATA_H\n\n')
    f.write(f'#define N {N}\n\n')
    f.write('double input_signal[N] = {\n')
    f.write(', '.join(map(str, input_signal)))
    f.write('\n};\n\n')
    f.write('double expected_output[N] = {\n')
    f.write(', '.join(map(str, expected_output)))
    f.write('\n};\n\n')
    f.write('#endif // AUTOCORR_DATA_H\n')

print("Header file 'autocorr_data.h' generated successfully.")
