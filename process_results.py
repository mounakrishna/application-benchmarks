import os
import csv

directory = "output/results"

result = []
fieldnames = ['Benchmark', 'Cycles', 'Instructions', 'Dual Issued', 'RAW Hazards', 'MEM BRANCH Hazards']

for filename in os.listdir(directory):
    filepath = os.path.join(directory, filename)
    with open(filepath, 'r') as file:
        content = file.readlines()
        data = {}
        #print(filename[8:])
        benchmark = filename[8:]
        data['Benchmark'] = benchmark
        for txt in content:
            if benchmark=="coremarks":
                if "ticks" in txt:
                    data["Cycles"] = txt.split()[-1]
                if "minstret" in txt:
                    data["Instructions"] = txt.split()[-1]
            elif benchmark == "BitNet":
                if "Cycles" in txt:
                    data["Cycles"] = txt.split()[-1]
                if "instructions" in txt:
                    data["Instructions"] = txt.split()[-1]
            elif benchmark == "xor_cipher":
                if "cycles" in txt:
                    if "Cycles" in data:
                        data["Cycles"] += int(txt.split()[-1])
                    else:
                        data["Cycles"] = int(txt.split()[-1])
                if "instructions" in txt:
                    if "Instructions" in data:
                        data["Instructions"] += txt.split()[-1]
                    else:
                        data["Instructions"] = txt.split()[-1]
            else:
                if "cycles" in txt or "Cycles" in txt:
                    data["Cycles"] = txt.split()[-1]
                if "instructions" in txt or "Instructions" in txt:
                    data["Instructions"] = txt.split()[-1]
            if "dual_issued" in txt:
                data["Dual Issued"] = txt.strip("dual_issued=").strip()
            if "raw_hazard" in txt:
                data["RAW Hazards"] = txt.strip("raw_hazard=").strip()
            if "mem_branch" in txt:
                data["MEM BRANCH Hazards"] = txt.strip("mem_branch_hazard=").strip()
    result.append(data)


with open('results.csv', 'w', newline='') as file:
    writer = csv.DictWriter(file, fieldnames=fieldnames)
    writer.writeheader()             # Write header row
    writer.writerows(result)            # Write data rows

print("CSV file 'people_dict.csv' created successfully.")
