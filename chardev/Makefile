KERNELDIR:=/home/wl/linux/linux-kernel/linux-4.1.15
CURRENT_PATH:=$(shell pwd)
INCLUDES_I:=-I$(KERNELDIR)/include

DIRS :=$(shell find $(CURRENT_PATH) -maxdepth 1 -type d)

SRC := $(foreach dir,$(DIRS),$(wildcard $(dir)/*.c))

OBJS :=$(patsubst %.c,%.o,$(SRC))

ARCH:=arm
CROSS_COMPILE:=arm-linux-gnueabihf-
AS:=$(CROSS_COMPILE)as
LD:=$(CROSS_COMPILE)ld
CC:=$(CROSS_COMPILE)gcc

obj-m:=chardri.o
chardri-objs=chardriver.o test.o
build:kernel_modules

kernel_modules:
	$(MAKE) -C $(KERNELDIR) ${INCLUDES_I} ARCH=${ARCH} NEED_OBJS=${chardri-objs} CROSS_COMPILE=${CROSS_COMPILE} M=$(CURRENT_PATH) modules 
	
clean:
	$(MAKE) -C $(KERNELDIR) M=$(CURRENT_PATH) clean
	
.PHONY:build clean


