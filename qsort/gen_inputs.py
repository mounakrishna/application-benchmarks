import random

# 8000 32-bit integers = 32,000 bytes (~31.25 kB)
# This is roughly double the 16kB D$ size, ensuring heavy cache thrashing.
ARRAY_SIZE = 8000 

def generate_header():
    # Seed for reproducibility in simulation testing
    random.seed(42) 
    
    # Generate random 32-bit signed integers
    input_data = [random.randint(-2147483648, 2147483647) for _ in range(ARRAY_SIZE)]
    # Generate reference sorted data
    reference_data = sorted(input_data)
    
    with open("qsort/inputs.h", "w") as f:
        f.write("/* Auto-generated test inputs for Shakti C-Class Cache Testing */\n\n")
        f.write(f"#define ARRAY_SIZE {ARRAY_SIZE}\n\n")
        
        # Write input array
        f.write("int input_array[ARRAY_SIZE] = {\n    ")
        f.write(",\n    ".join(map(str, input_data)))
        f.write("\n};\n\n")
        
        # Write golden/reference array
        f.write("int reference_array[ARRAY_SIZE] = {\n    ")
        f.write(",\n    ".join(map(str, reference_data)))
        f.write("\n};\n")

    print(f"Success: inputs.h generated with {ARRAY_SIZE} elements (~32kB).")

if __name__ == "__main__":
    generate_header()
