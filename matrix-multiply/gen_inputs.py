import random
import sys

matrix_size = sys.argv[1]

if __name__ == "__main__":
    inp_file = open("matrix-multiply/inputs.h", 'w')
    inp_file.write("#include <stdio.h>\n")
    inp_file.write('#include "params.h"\n\n')

    # Matrix 1 write
    inp_file.write("type matrix1[" + matrix_size + "][" + matrix_size +"] = {\n")
    for i in range(int(matrix_size)):
        inp_file.write("\t\t{")
        for j in range(int(matrix_size)):
            r = random.randint(0, 99)
            inp_file.write(str(r))
            if (j != int(matrix_size) - 1):
                inp_file.write(", ")
        inp_file.write("},\n")
    inp_file.write("};\n")

    # Matrix 2 write
    inp_file.write("type matrix2[" + matrix_size + "][" + matrix_size +"] = {\n")
    for i in range(int(matrix_size)):
        inp_file.write("\t\t{")
        for j in range(int(matrix_size)):
            r = random.randint(0, 99)
            inp_file.write(str(r))
            if (j != int(matrix_size) - 1):
                inp_file.write(", ")
        inp_file.write("},\n")
    inp_file.write("};\n")
