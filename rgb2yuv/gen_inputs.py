import random
import sys

height = sys.argv[1]
weight = sys.argv[2]

def random_gen(inp_file):
    for i in range(int(matrix_size)):
        inp_file.write("\t\t{")
        for j in range(int(matrix_size)):
            r = random.randint(0, 255)
            inp_file.write(str(r))
            if (j != int(matrix_size) - 1):
                inp_file.write(", ")
        inp_file.write("},\n")
    inp_file.write("};\n")

if __name__ == "__main__":
    inp_file = open("rgb2yuv/inputs.h", 'w')
    inp_file.write("#include <stdio.h>\n")
    #inp_file.write('#include "params.h"\n\n')

    # Image write
    inp_file.write("uint8_t img_r[" + height + "][" + weight +"] = {\n")
    random_gen(inp_file)
    inp_file.write("\n")

    inp_file.write("uint8_t img_g[" + height + "][" + weight +"] = {\n")
    random_gen(inp_file)
    inp_file.write("\n")

    inp_file.write("uint8_t img_b[" + height + "][" + weight +"] = {\n")
    random_gen(inp_file)
    inp_file.write("\n")

    inp_file.close()
