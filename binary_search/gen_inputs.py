import numpy as np
import sys

N = int(sys.argv[1])  # Number of elements in the array
K = int(sys.argv[2])  # Number of queries
np.random.seed(0)
input_array = np.sort(np.random.randint(0, 100, size=N))

# Build K random search keys, some guaranteed to exist, some might not
in_keys = np.random.choice(input_array, size=K//2, replace=False)          # existing values
out_keys = np.random.randint(100, 200, size=(K - K//2))                    # unlikely to exist
search_keys = np.concatenate([in_keys, out_keys])
np.random.shuffle(search_keys)

# Expected indices: np.searchsorted returns insertion point, but we want index if exists, else -1
def true_index(arr, key):
    idxs = np.where(arr == key)[0]
    return int(idxs[0]) if len(idxs) > 0 else -1

expected_indices = [true_index(input_array, k) for k in search_keys]

with open('binary_search/inputs.h', 'w') as f:
    f.write('#ifndef BINARY_DATA_H\n#define BINARY_DATA_H\n\n')
    f.write(f'#define N {N}\n#define K {K}\n\n')
    f.write('int input_array[N] = {\n  ')
    f.write(', '.join(map(str, input_array)))
    f.write('\n};\n\n')
    f.write('int search_keys[K] = {\n  ')
    f.write(', '.join(map(str, search_keys)))
    f.write('\n};\n\n')
    f.write('int expected_indices[K] = {\n  ')
    f.write(', '.join(map(str, expected_indices)))
    f.write('\n};\n\n')
    f.write('#endif // BINARY_DATA_H\n')
print("Header file 'binary_data.h' generated successfully.")
