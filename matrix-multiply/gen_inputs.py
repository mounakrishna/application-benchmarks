import random
import sys

def generate_matrix(rows, cols, low=0, high=99):
    return [[random.randint(low, high) for _ in range(cols)] for _ in range(rows)]

def matrix_multiply(A, B):
    result = []
    for i in range(len(A)):
        row = []
        for j in range(len(B[0])):
            s = 0
            for k in range(len(A[0])):
                s += A[i][k] * B[k][j]
            row.append(s)
        result.append(row)
    return result

def to_c_array(name, matrix, dtype="int"):
    rows = len(matrix)
    cols = len(matrix[0])
    c_str = f"{dtype} {name}[{rows}][{cols}] = {{\n"
    for row in matrix:
        row_str = ", ".join(str(val) for val in row)
        c_str += f"    {{ {row_str} }},\n"
    c_str += "};\n"
    return c_str

# Set matrix size (e.g., 4x4)
n = int(sys.argv[1])
A = generate_matrix(n, n)
B = generate_matrix(n, n)
C = matrix_multiply(A, B)

header_content = "// Generated input matrices and expected matrix multiplication output for verification\n"
header_content += "#include <stdio.h>\n"
header_content += "#include \"params.h\"\n"
header_content += to_c_array("matrix1", A, dtype="type")
header_content += "\n"
header_content += to_c_array("matrix2", B, dtype="type")
header_content += "\n"
header_content += to_c_array("expected_result_matrix", C, dtype="type")

with open("matrix-multiply/inputs.h", "w") as file:
    file.write(header_content)
