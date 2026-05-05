import random

def generate_sample_sad_blocks():
    pix1 = [[random.randint(0, 255) for _ in range(16)] for _ in range(16)]
    pix2 = []
    for row in pix1:
        new_row = []
        for val in row:
            variation = random.randint(-10, 10)
            new_val = max(0, min(255, val + variation))
            new_row.append(new_val)
        pix2.append(new_row)
    return pix1, pix2

def to_c_array(name, matrix):
    c_str = f"unsigned char {name}[16][16] = {{\n"
    for row in matrix:
        row_str = ", ".join(str(pixel) for pixel in row)
        c_str += f"    {{ {row_str} }},\n"
    c_str += "};\n"
    return c_str

def compute_sad(pix1, pix2):
    i_sum = 0
    for y in range(16):
        for x in range(16):
            i_sum += abs(pix1[y][x] - pix2[y][x])
    return i_sum

pix1, pix2 = generate_sample_sad_blocks()
sad_value = compute_sad(pix1, pix2)
c_pix1 = to_c_array("pix1", pix1)
c_pix2 = to_c_array("pix2", pix2)
sad_c = f"const int expected_sad = {sad_value};\n"

header_content = "// Generated input pixel data for SAD testing\n" 
header_content += "typedef unsigned char pixel;\n"
header_content += c_pix1 + "\n" + c_pix2 + "\n" + sad_c

with open("pixel_sad/inputs.h", "w") as file:
    file.write(header_content)

# Write pix1 and pix2 blocks to console or to files as needed:
#print(c_pix1)
#print(c_pix2)
