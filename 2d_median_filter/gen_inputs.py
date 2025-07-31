import numpy as np
import sys
from scipy.signal import medfilt2d

# Parameters
rows, cols = int(sys.argv[1]), int(sys.argv[1])          # Image size - adjust as needed
kernel_size = int(sys.argv[2])              # Median filter window size; use odd integer
np.random.seed(0)

input_image = np.random.randint(0, 256, size=(rows, cols), dtype=np.uint8)
expected_output = medfilt2d(input_image, kernel_size=kernel_size).astype(np.uint8)

with open('2d_median_filter/inputs.h', 'w') as f:
    f.write('#ifndef MEDIAN_DATA_H\n#define MEDIAN_DATA_H\n\n')
    f.write(f'#define ROWS {rows}\n#define COLS {cols}\n#define KERNEL_SIZE {kernel_size}\n\n')
    f.write('unsigned char input_image[ROWS][COLS] = {\n')
    for row in input_image:
        f.write('    { ' + ', '.join(map(str, row)) + ' },\n')
    f.write('};\n\n')
    f.write('unsigned char expected_output[ROWS][COLS] = {\n')
    for row in expected_output:
        f.write('    { ' + ', '.join(map(str, row)) + ' },\n')
    f.write('};\n\n')
    f.write('#endif // MEDIAN_DATA_H\n')

print("Header file 'median_data.h' generated successfully.")

