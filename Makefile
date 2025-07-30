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
				-DITERATIONS=$(ITERATIONS) -D$(target)=True -mcmodel=medany -static -std=gnu99 -O2 -ffast-math \
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
				-D$(target)=True -DDEBUG -DMATRIX_SIZE=$(MATRIX_SIZE) -D$(COMPUTE_SIZE) -DITERATIONS=$(ITERATIONS) \
				-mcmodel=medany -static -std=gnu99 -O -ffast-math \
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
				-mcmodel=medany -static -std=gnu99 -O -ffast-math \
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
				-D$(target)=True -mcmodel=medany -static -std=gnu99 -O -ffast-math \
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
		-mcmodel=medany -static -std=gnu99 -O -ffast-math \
		-fno-common -fno-builtin-printf -march=rv$(xlen)$(march) -w -static \
		-nostartfiles -lgcc -T ./common/link.ld -o $(OUTDIR)/BitNet.riscv ./BitNet/BitNetMCUdemo.c \
		./common/syscalls.c ./common/crt.S
	@$(RISCV_OBJDUMP) $(OUTDIR)/BitNet.riscv > $(OUTDIR)/BitNet.dump
	@$(RISCV_HEX) $(OUTDIR)/BitNet.riscv 2147483648 > $(OUTDIR)/code.mem

.PHONY: clean
clean:
	rm -rf $(OUTDIR)
