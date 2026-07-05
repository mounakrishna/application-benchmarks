xlen ?= 64
linesize=$$(($(xlen)/8))
target ?= CUSTOM
ITERATIONS ?= 1
HPM_ENABLE ?= 1 #1 enable ,0 disable
march ?= imafdc
RISCV_PREFIX ?= riscv$(xlen)-unknown-elf-
RISCV_GCC ?= $(RISCV_PREFIX)gcc
RISCV_LINK_OPTS ?= -static -nostartfiles -lgcc -T ./common/link.ld
RISCV_HEX = elf2hex $(linesize) 4194304
RISCV_OBJDUMP ?= $(RISCV_PREFIX)objdump -D
OUTDIR ?= output
FLAGS_STR = -mcmodel=medany -D$(target) -DPERFORMANCE_RUN=1 -DMAIN_HAS_NOARGC=1 -DHAS_STDIO \
					  -DHAS_PRINTF -DHAS_FLOAT=0 -DITERATIONS=$(ITERATIONS) \
						-O3 -fno-common -funroll-loops -finline-functions -fselective-scheduling \
						-falign-functions=16 -falign-jumps=4 -falign-loops=4 -finline-limit=1000 \
					 	-nostartfiles -nostdlib -ffast-math -fno-builtin-printf -march=rv$(xlen)$(march)\
						-mexplicit-relocs -DHPM_ENABLE=$(HPM_ENABLE)



.PHONY: dhrystone
dhrystone: 
	@echo "Compiling Dhrystone"
	@mkdir -p output/
	@$(RISCV_GCC) -I./common -D$(target) -DCONFIG_RISCV64=True -mcmodel=medany -static -std=gnu99\
		-O2 -ffast-math -fno-common -fno-builtin-printf -march=rv$(xlen)$(march) -mabi=lp64d -w -static\
		-nostartfiles -lgcc -c common/crt.S -o output/crt.o
	@$(RISCV_GCC) -I./common -D$(target) -DCONFIG_RISCV64=True -mcmodel=medany -static -std=gnu99\
		-O -ffast-math -fno-common -fno-builtin-printf -march=rv$(xlen)$(march) -mabi=lp64d -w -static\
		-nostartfiles -lgcc -c common/syscalls.c -o output/syscalls.o
	$(RISCV_GCC) -I./common -I./dhrystone -DCONFIG_RISCV64=True \
				-DITERATIONS=$(ITERATIONS) -DHPM_ENABLE=$(HPM_ENABLE) -D$(target)=True -mcmodel=medany -static -std=gnu99 -O2 -ffast-math \
				-fno-common -fno-builtin-printf -march=rv$(xlen)$(march) -mabi=lp64d \
				-w -static -nostartfiles -lgcc -T ./common/link.ld -o $(OUTDIR)/dhry.riscv \
				./dhrystone/dhry_1.c ./dhrystone/dhry_2.c ./output/syscalls.o ./output/crt.o
	@$(RISCV_OBJDUMP) $(OUTDIR)/dhry.riscv > $(OUTDIR)/dhry.dump
	@$(RISCV_HEX) $(OUTDIR)/dhry.riscv 2147483648 > $(OUTDIR)/code.mem

.PHONY: stream
stream: 
	@echo "Compiling Stream"
	@mkdir -p output/
	@$(RISCV_GCC) -I./common -D$(target) -DCONFIG_RISCV64=True -mcmodel=medany -static -std=gnu99\
		-O2 -ffast-math -fno-common -fno-builtin-printf -march=rv$(xlen)$(march) -mabi=lp64d -w -static\
		-nostartfiles -lgcc -c common/crt.S -o output/crt.o
	@$(RISCV_GCC) -I./common -D$(target) -DCONFIG_RISCV64=True -mcmodel=medany -static -std=gnu99\
		-O -ffast-math -fno-common -fno-builtin-printf -march=rv$(xlen)$(march) -mabi=lp64d -w -static\
		-nostartfiles -lgcc -c common/syscalls.c -o output/syscalls.o
	$(RISCV_GCC) -I./common -I./STREAM -DCONFIG_RISCV64=True \
				-DITERATIONS=$(ITERATIONS) -D$(target)=True -mcmodel=medany -static -std=gnu99 -O2 -ffast-math \
				-fno-common -fno-builtin-printf -march=rv$(xlen)$(march) -mabi=lp64d \
				-w -static -nostartfiles -lgcc -T ./common/link.ld -o $(OUTDIR)/stream.riscv \
				./STREAM/stream.c ./STREAM/mysecond.c ./output/syscalls.o ./output/crt.o
	@$(RISCV_OBJDUMP) $(OUTDIR)/stream.riscv > $(OUTDIR)/stream.dump
	@$(RISCV_HEX) $(OUTDIR)/stream.riscv 2147483648 > $(OUTDIR)/code.mem


.PHONY: hello
hello:
	@echo "Compiling Hello-Shakti"
	@mkdir -p output/
	$(RISCV_GCC) -I./common -I./hello -DCONFIG_RISCV64=True \
				-D$(target)=True -mcmodel=medany -static -std=gnu99 -O -ffast-math \
				-fno-common -fno-builtin-printf -march=rv$(xlen)$(march) -w -static \
				-nostartfiles -lgcc -T ./common/link.ld -o $(OUTDIR)/hello.riscv ./hello/hello.c \
				./common/syscalls.c ./common/crt.S
	@$(RISCV_OBJDUMP) $(OUTDIR)/hello.riscv > $(OUTDIR)/hello.dump
	@$(RISCV_HEX) $(OUTDIR)/hello.riscv 2147483648 > $(OUTDIR)/code.mem


.PHONY: coremarks
coremarks:
	@echo "Compiling Coremarks"
	@mkdir -p output/
	@$(RISCV_GCC) -I./common -D$(target) -g -DCONFIG_RISCV64=True -mcmodel=medany -static -std=gnu99\
		-O2 -ffast-math -fno-common -fno-builtin-printf -march=rv$(xlen)$(march) -w -static\
		-nostartfiles -lgcc -c common/crt.S -o output/crt.o
	@$(RISCV_GCC) -I./common -D$(target) -g -DCONFIG_RISCV64=True -mcmodel=medany -static -std=gnu99\
		-O -ffast-math -fno-common -fno-builtin-printf -march=rv$(xlen)$(march) -w -static\
		-nostartfiles -lgcc -c common/syscalls.c -o output/syscalls.o
	$(RISCV_GCC) -I./common -I./coremarks -g $(FLAGS_STR) $(RISCV_LINK_OPTS) -o $(OUTDIR)/coremarks.riscv \
		./coremarks/core_util.c ./coremarks/ee_printf.c ./coremarks/core_state.c \
		-DFLAGSTR=\"$(FLAGS)\" \
		./coremarks/core_list_join.c ./coremarks/core_portme.c ./coremarks/core_main.c \
		./coremarks/core_matrix.c ./output/crt.o ./output/syscalls.o
	@$(RISCV_OBJDUMP) -S $(OUTDIR)/coremarks.riscv > $(OUTDIR)/coremarks.dump
	@$(RISCV_HEX) $(OUTDIR)/coremarks.riscv 2147483648 > $(OUTDIR)/code.mem

COMPUTE_SIZE:=u16
ITERATION:=10
MATRIX_SIZE:=4

.PHONY: matrix-multiply
matrix-multiply:
	@echo "Compiling Matrix multiply"
	@mkdir -p output/
	@python3 matrix-multiply/gen_inputs.py $(MATRIX_SIZE)
	$(RISCV_GCC) -I./common -I./matrix-multiply -DCONFIG_RISCV64=True \
				-D$(target)=True -DHPM_ENABLE=$(HPM_ENABLE) -DMATRIX_SIZE=$(MATRIX_SIZE) -D$(COMPUTE_SIZE) -DITERATIONS=$(ITERATIONS) \
				-mcmodel=medany -static -std=gnu99 -O2 -ffast-math \
				-fno-common -fno-builtin-printf -march=rv$(xlen)$(march) -w -static \
				-nostartfiles -lgcc -T ./common/link.ld -o $(OUTDIR)/matrix-multiply.riscv ./matrix-multiply/matrix-multiply.c \
				./common/syscalls.c ./common/crt.S
	@$(RISCV_OBJDUMP) $(OUTDIR)/matrix-multiply.riscv > $(OUTDIR)/matrix-multiply.dump
	@$(RISCV_HEX) $(OUTDIR)/matrix-multiply.riscv 2147483648 > $(OUTDIR)/code.mem

.PHONY: pixel_sad
pixel_sad:
	@echo "Compiling SAD16x16"
	@mkdir -p output/
	@python3 pixel_sad/input_generator.py
	$(RISCV_GCC) -I./common -I./pixel_sad -g -DCONFIG_RISCV64=True \
				-D$(target)=True -DHPM_ENABLE=$(HPM_ENABLE) -DITERATIONS=$(ITERATIONS) \
				-mcmodel=medany -static -std=gnu99 -O2 -ffast-math \
				-fno-common -fno-builtin-printf -march=rv$(xlen)$(march) -w -static \
				-nostartfiles -lgcc -T ./common/link.ld -o $(OUTDIR)/pixel_sad.riscv ./pixel_sad/pixel_sad.c \
				./common/syscalls.c ./common/crt.S
	@$(RISCV_OBJDUMP) -S $(OUTDIR)/pixel_sad.riscv > $(OUTDIR)/pixel_sad.dump
	@$(RISCV_HEX) $(OUTDIR)/pixel_sad.riscv 2147483648 > $(OUTDIR)/code.mem

.PHONY: conv2d
conv2d:
	@echo "Compiling 2-D Convolution "
	@mkdir -p output/
	$(RISCV_GCC) -I./common -I./conv2d -DCONFIG_RISCV64=True \
				-D$(target)=True -DITERATIONS=$(ITERATINS) -mcmodel=medany -static -std=gnu99 -O2 -ffast-math \
				-fno-common -fno-builtin-printf -march=rv$(xlen)$(march) -w -static \
				-nostartfiles -lgcc -T ./common/link.ld -o $(OUTDIR)/conv2d.riscv ./conv2d/conv2d.c \
				./common/syscalls.c ./common/crt.S
	@$(RISCV_OBJDUMP) $(OUTDIR)/conv2d.riscv > $(OUTDIR)/conv2d.dump
	@$(RISCV_HEX) $(OUTDIR)/conv2d.riscv 2147483648 > $(OUTDIR)/code.mem

.PHONY: BitNet
BitNet:
	@echo "Compiling BitNet"
	@mkdir -p output/
	$(RISCV_GCC) -I./common -I./BitNet -DCONFIG_RISCV64=True \
		-D$(target)=True -DITERATIONS=$(ITERATIONS) -DHPM_ENABLE=$(HPM_ENABLE) \
		-mcmodel=medany -static -std=gnu99 -O2 -ffast-math \
		-fno-common -fno-builtin-printf -march=rv$(xlen)$(march) -w -static \
		-nostartfiles -lgcc -T ./common/link.ld -o $(OUTDIR)/BitNet.riscv ./BitNet/BitNetMCUdemo.c \
		./common/syscalls.c ./common/crt.S
	@$(RISCV_OBJDUMP) $(OUTDIR)/BitNet.riscv > $(OUTDIR)/BitNet.dump
	@$(RISCV_HEX) $(OUTDIR)/BitNet.riscv 2147483648 > $(OUTDIR)/code.mem

TEXT_LEN:=32
.PHONY: xor_cipher
xor_cipher:
	@echo "Compiling XOR Cipher"
	@mkdir -p output/
	@python3 xor_cipher/gen_inputs.py $(TEXT_LEN)
	$(RISCV_GCC) -I./common -I./xor_cipher -DCONFIG_RISCV64=True \
				-D$(target)=True -DHPM_ENABLE=$(HPM_ENABLE) -DITERATIONS=$(ITERATIONS) \
				-mcmodel=medany -static -std=gnu99 -O2 -ffast-math \
				-fno-common -fno-builtin-printf -march=rv$(xlen)$(march) -w -static \
				-nostartfiles -lgcc -T ./common/link.ld -o $(OUTDIR)/xor_cipher.riscv ./xor_cipher/xor_cipher.c \
				./common/syscalls.c ./common/crt.S
	@$(RISCV_OBJDUMP) $(OUTDIR)/xor_cipher.riscv > $(OUTDIR)/xor_cipher.dump
	@$(RISCV_HEX) $(OUTDIR)/xor_cipher.riscv 2147483648 > $(OUTDIR)/code.mem

VEC_SIZE:= 20
.PHONY: vec_add
vec_add:
	@echo "Compiling Vector add"
	@mkdir -p output/
	@python3 vec_add/gen_inputs.py $(VEC_SIZE)
	$(RISCV_GCC) -I./common -I./vec_add -DCONFIG_RISCV64=True \
				-D$(target)=True -DHPM_ENABLE=$(HPM_ENABLE) -DITERATIONS=$(ITERATIONS) \
				-mcmodel=medany -static -std=gnu99 -O2 -ffast-math \
				-fno-common -fno-builtin-printf -march=rv$(xlen)$(march) -w -static \
				-nostartfiles -lgcc -T ./common/link.ld -o $(OUTDIR)/vec_add.riscv ./vec_add/vec_add.c \
				./common/syscalls.c ./common/crt.S
	@$(RISCV_OBJDUMP) $(OUTDIR)/vec_add.riscv > $(OUTDIR)/vec_add.dump
	@$(RISCV_HEX) $(OUTDIR)/vec_add.riscv 2147483648 > $(OUTDIR)/code.mem

ARR_SIZE:= 20
.PHONY: insertion_sort
insertion_sort:
	@echo "Compiling Insertion Sort"
	@mkdir -p output/
	@python3 insertion_sort/gen_inputs.py $(ARR_SIZE)
	$(RISCV_GCC) -I./common -I./insertion_sort -DCONFIG_RISCV64=True \
				-D$(target)=True -DHPM_ENABLE=$(HPM_ENABLE) -DITERATIONS=$(ITERATIONS) \
				-mcmodel=medany -static -std=gnu99 -O2 -ffast-math \
				-fno-common -fno-builtin-printf -march=rv$(xlen)$(march) -w -static \
				-nostartfiles -lgcc -T ./common/link.ld -o $(OUTDIR)/insertion_sort.riscv ./insertion_sort/insertion_sort.c \
				./common/syscalls.c ./common/crt.S
	@$(RISCV_OBJDUMP) $(OUTDIR)/insertion_sort.riscv > $(OUTDIR)/insertion_sort.dump
	@$(RISCV_HEX) $(OUTDIR)/insertion_sort.riscv 2147483648 > $(OUTDIR)/code.mem

.PHONY: bubblesort
bubblesort:
	@echo "Compiling bubblesort"
	@mkdir -p output/
	@python3 bubblesort/gen_inputs.py $(ARR_SIZE)
	$(RISCV_GCC) -I./common -I./bubblesort -DCONFIG_RISCV64=True \
				-D$(target)=True -DHPM_ENABLE=$(HPM_ENABLE) -DITERATIONS=$(ITERATIONS) \
				-mcmodel=medany -static -std=gnu99 -O2 -ffast-math \
				-fno-common -fno-builtin-printf -march=rv$(xlen)$(march) -w -static \
				-nostartfiles -lgcc -T ./common/link.ld -o $(OUTDIR)/bubblesort.riscv ./bubblesort/bubblesort.c \
				./common/syscalls.c ./common/crt.S
	@$(RISCV_OBJDUMP) $(OUTDIR)/bubblesort.riscv > $(OUTDIR)/bubblesort.dump
	@$(RISCV_HEX) $(OUTDIR)/bubblesort.riscv 2147483648 > $(OUTDIR)/code.mem

FIR_INP_SIZE:= 100
FIR_LEN:= 16
.PHONY: fir_filter
fir_filter:
	@echo "Compiling FIR Filter"
	@mkdir -p output/
	@python3 fir_filter/gen_inputs.py $(FIR_INP_SIZE) $(FIR_LEN)
	$(RISCV_GCC) -I./common -I./fir_filter -DCONFIG_RISCV64=True \
				-D$(target)=True -DHPM_ENABLE=$(HPM_ENABLE) -DITERATIONS=$(ITERATIONS) \
				-mcmodel=medany -static -std=gnu99 -O2 -ffast-math \
				-fno-common -fno-builtin-printf -march=rv$(xlen)$(march) -w -static \
				-nostartfiles -lgcc -T ./common/link.ld -o $(OUTDIR)/fir_filter.riscv ./fir_filter/fir_filter.c \
				./common/syscalls.c ./common/crt.S
	@$(RISCV_OBJDUMP) $(OUTDIR)/fir_filter.riscv > $(OUTDIR)/fir_filter.dump
	@$(RISCV_HEX) $(OUTDIR)/fir_filter.riscv 2147483648 > $(OUTDIR)/code.mem

.PHONY: factorial
factorial:
	@echo "Compiling Factorial"
	@mkdir -p output/
	@python3 factorial/gen_inputs.py
	$(RISCV_GCC) -I./common -I./factorial -DCONFIG_RISCV64=True \
				-D$(target)=True -DHPM_ENABLE=$(HPM_ENABLE) -DITERATIONS=$(ITERATIONS) \
				-mcmodel=medany -static -std=gnu99 -O2 -ffast-math \
				-fno-common -fno-builtin-printf -march=rv$(xlen)$(march) -w -static \
				-nostartfiles -lgcc -T ./common/link.ld -o $(OUTDIR)/factorial.riscv ./factorial/factorial.c \
				./common/syscalls.c ./common/crt.S
	@$(RISCV_OBJDUMP) $(OUTDIR)/factorial.riscv > $(OUTDIR)/factorial.dump
	@$(RISCV_HEX) $(OUTDIR)/factorial.riscv 2147483648 > $(OUTDIR)/code.mem

QUERY_SIZE:=10
.PHONY: binary_search
binary_search:
	@echo "Compiling Binary Search"
	@mkdir -p output/
	@python3 binary_search/gen_inputs.py $(ARR_SIZE) $(QUERY_SIZE)
	$(RISCV_GCC) -I./common -I./binary_search -DCONFIG_RISCV64=True \
				-D$(target)=True -DHPM_ENABLE=$(HPM_ENABLE) -DITERATIONS=$(ITERATIONS) \
				-mcmodel=medany -static -std=gnu99 -O2 -ffast-math \
				-fno-common -fno-builtin-printf -march=rv$(xlen)$(march) -w -static \
				-nostartfiles -lgcc -T ./common/link.ld -o $(OUTDIR)/binary_search.riscv ./binary_search/binary_search.c \
				./common/syscalls.c ./common/crt.S
	@$(RISCV_OBJDUMP) $(OUTDIR)/binary_search.riscv > $(OUTDIR)/binary_search.dump
	@$(RISCV_HEX) $(OUTDIR)/binary_search.riscv 2147483648 > $(OUTDIR)/code.mem

.PHONY: qsort
qsort:
	@echo "Compiling Quick Sort"
	@mkdir -p output/
	@python3 qsort/gen_inputs.py
	$(RISCV_GCC) -I./common -I./qsort -DCONFIG_RISCV64=True \
				-D$(target)=True -DHPM_ENABLE=$(HPM_ENABLE) -DITERATIONS=$(ITERATIONS) \
				-mcmodel=medany -static -std=gnu99 -O2 -ffast-math \
				-fno-common -fno-builtin-printf -march=rv$(xlen)$(march) -w -static \
				-nostartfiles -lgcc -T ./common/link.ld -o $(OUTDIR)/qsort.riscv ./qsort/qsort.c \
				./common/syscalls.c ./common/crt.S
	@$(RISCV_OBJDUMP) $(OUTDIR)/qsort.riscv > $(OUTDIR)/qsort.dump
	@$(RISCV_HEX) $(OUTDIR)/qsort.riscv 2147483648 > $(OUTDIR)/code.mem

INP_SIZE:=100
.PHONY: autocorrelation
autocorrelation:
	@echo "Compiling AutoCorrelation"
	@mkdir -p output/
	@python3 autocorrelation/gen_inputs.py $(INP_SIZE)
	$(RISCV_GCC) -I./common -I./autocorrelation -DCONFIG_RISCV64=True \
				-D$(target)=True -DHPM_ENABLE=$(HPM_ENABLE) -DITERATIONS=$(ITERATIONS) \
				-mcmodel=medany -static -std=gnu99 -O2 -ffast-math \
				-fno-common -fno-builtin-printf -march=rv$(xlen)$(march) -w -static \
				-nostartfiles -lgcc -T ./common/link.ld -o $(OUTDIR)/autocorrelation.riscv ./autocorrelation/autocorrelation.c \
				./common/syscalls.c ./common/crt.S
	@$(RISCV_OBJDUMP) $(OUTDIR)/autocorrelation.riscv > $(OUTDIR)/autocorrelation.dump
	@$(RISCV_HEX) $(OUTDIR)/autocorrelation.riscv 2147483648 > $(OUTDIR)/code.mem

IMG_SIZE:=10
KERNEL_SIZE:=3
.PHONY: 2d_median_filter
2d_median_filter:
	@echo "Compiling 2D Median Filter"
	@mkdir -p output/
	@python3 2d_median_filter/gen_inputs.py $(IMG_SIZE) $(KERNEL_SIZE)
	$(RISCV_GCC) -I./common -I./2d_median_filter -DCONFIG_RISCV64=True \
				-D$(target)=True -DHPM_ENABLE=$(HPM_ENABLE) -DITERATIONS=$(ITERATIONS) \
				-mcmodel=medany -static -std=gnu99 -O2 -ffast-math \
				-fno-common -fno-builtin-printf -march=rv$(xlen)$(march) -w -static \
				-nostartfiles -lgcc -T ./common/link.ld -o $(OUTDIR)/2d_median_filter.riscv ./2d_median_filter/2d_median_filter.c \
				./common/syscalls.c ./common/crt.S
	@$(RISCV_OBJDUMP) $(OUTDIR)/2d_median_filter.riscv > $(OUTDIR)/2d_median_filter.dump
	@$(RISCV_HEX) $(OUTDIR)/2d_median_filter.riscv 2147483648 > $(OUTDIR)/code.mem


.PHONY: clean
clean:
	rm -rf $(OUTDIR)
