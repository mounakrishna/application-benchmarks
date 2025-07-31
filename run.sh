mkdir -p output/results

#benchmarks=("coremarks" "BitNet" "matrix-multiply" "pixel_sad" "dhrystone" "xor_cipher" "vec_add" "insertion_sort" "bubblesort" "fir_filter" "factorial" "binary_search" "autocorrelation" "2d_median_filter")
#parameters=("ITERATIONS=40"  "ITERATIONS=5"  "MATRIX_SIZE=16 ITERATIONS=40"  ""  "TEXT_LEN=256"  "VEC_SIZE=100"  "ARR_SIZE=100"  "ARR_SIZE=100"  "FIR_INP_SIZE=100 FIR_LEN=16"  ""  "ARR_SIZE=100 QUERY_SIZE=50"  "INP_SIZE=100"  "IMG_SIZE=10 KERNEL_SIZE=3")
declare -A benchmarks
benchmarks["coremarks"]="ITERATIONS=100"
benchmarks["BitNet"]="ITERATIONS=5"
benchmarks["matrix-multiply"]="ITERATIONS=100 MATRIX_SIZE=16"
benchmarks["pixel_sad"]="ITERATIONS=100"
benchmarks["dhrystone"]="ITERATIONS=100"
benchmarks["xor_cipher"]="ITERATIONS=100 TEXT_LEN=256"
benchmarks["vec_add"]="ITERATIONS=100 VEC_SIZE=100"
benchmarks["insertion_sort"]="ITERATIONS=100 ARR_SIZE=100"
benchmarks["bubblesort"]="ITERATIONS=100 ARR_SIZE=100"
benchmarks["fir_filter"]="ITERATIONS=100 FIR_INP_SIZE=100 FIR_LEN=16"
benchmarks["factorial"]="ITERATIONS=100"
benchmarks["binary_search"]="ITERATIONS=100 ARR_SIZE=100 QUERY_SIZE=50"
benchmarks["autocorrelation"]="ITERATIONS=100 INP_SIZE=100"
benchmarks["2d_median_filter"]="ITERATIONS=100 IMG_SIZE=10 KERNEL_SIZE=3"
length=${#benchmarks[@]}

for benchmark in "${!benchmarks[@]}"; do
  make ${benchmark} ${benchmarks[$benchmark]}
  cd output; ./out;
  mv app_log results/app_log_${benchmark}
  cd ../
done
