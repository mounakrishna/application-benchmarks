import os
import csv

suffix = 'btb32_instrQ2'
directory = "output/results_" + suffix

result = []
fieldnames = ['Benchmark', 'Iterations', 'Cycles', 'Instructions', 'Branches', 'Jumps', 'Mispredictions', 'Dual Issued', 'RAW Hazards', 'MEM BRANCH Hazards', 'IPC']

for filename in os.listdir(directory):
    filepath = os.path.join(directory, filename)
    with open(filepath, 'r') as file:
        content = file.readlines()
        data = {}
        benchmark = filename[8:]
        data['Benchmark'] = benchmark
        for txt in content:
            if benchmark=="coremarks":
                if "ticks" in txt:
                    data["Cycles"] = txt.split()[-1]
                if "minstret" in txt:
                    data["Instructions"] = txt.split()[-1]
                if "Iterations" in txt:
                    data["Iterations"] = txt.split()[-1]
            elif benchmark == "BitNet":
                if "Cycles" in txt:
                    data["Cycles"] = txt.split()[-1]
                if "instructions" in txt:
                    data["Instructions"] = txt.split()[-1]
                if "iterations" in txt:
                    data["Iterations"] = txt.split()[-1]
            elif benchmark == "xor_cipher":
                if "cycles" in txt:
                    if "Cycles" in data:
                        data["Cycles"] += int(txt.split()[-1]) 
                    else:
                        data["Cycles"] = int(txt.split()[-1])
                if "instructions" in txt:
                    if "Instructions" in data:
                        data["Instructions"] += int(txt.split()[-1])
                    else:
                        data["Instructions"] = int(txt.split()[-1])
                if "iterations" in txt:
                    data["Iterations"] = txt.split()[-1]
            else:
                if "cycles" in txt or "Cycles" in txt:
                    data["Cycles"] = txt.split()[-1]
                if "instructions" in txt or "Instructions" in txt:
                    data["Instructions"] = txt.split()[-1]
                if "iterations" in txt:
                    data["Iterations"] = txt.split()[-1]

            if "branches" in txt:
                data["Branches"] = txt.strip("branches=").strip()
            if "jumps" in txt:
                data["Jumps"] = txt.strip("jumps=").strip()
            if "misprediction" in txt:
                data["Mispredictions"] = txt.strip("misprediction =").strip()
            if "dual_issued" in txt:
                data["Dual Issued"] = txt.strip("dual_issued=").strip()
            if "raw_hazard" in txt:
                data["RAW Hazards"] = txt.strip("raw_hazard=").strip()
            if "mem_branch" in txt:
                data["MEM BRANCH Hazards"] = txt.strip("mem_branch_hazard=").strip()
        data["IPC"] = round(float(data["Instructions"]) / float(data["Cycles"]), 3)
    result.append(data)


total_ipc = 0
number_of_benchmarks = len(result)
for data in result:
    total_ipc += float(data["IPC"])
avg_ipc = round(total_ipc / number_of_benchmarks, 4)

with open('results_' + suffix + '.csv', 'w', newline='') as file:
    writer = csv.DictWriter(file, fieldnames=fieldnames)
    writer.writeheader()             # Write header row
    writer.writerows(result)            # Write data rows
    #writer.writerow([""])

with open('results_' + suffix + '.csv', 'a', newline='') as csvfile:
    writer = csv.writer(csvfile)
    writer.writerow([''])
    writer.writerow(["Average IPC"] + [avg_ipc])


print("CSV file 'people_dict.csv' created successfully.")
