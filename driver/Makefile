CROSS_COMPILE := aarch64-linux-gnu-
ARCH := arm64
CC := $(CROSS_COMPILE)gcc
LD := $(CROSS_COMPILE)ld
obj-m += smc_fuzz.o
smc_fuzz-objs := smc_fuzz_main.o smc_parse.o
KERNELDIR := /home/dell/paper/tee/cca-v3/linux

.PHONY: all clean

all:
	make ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(KERNELDIR) M=$(PWD)/driver modules

clean:
	make ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(KERNELDIR) M=$(PWD)/driver clean

