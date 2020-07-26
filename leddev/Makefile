KERNELDIR:=/home/wl/linux/linux-kernel/linux-4.1.15
CURRENT_PATH:=$(shell pwd)

DIRS :=$(shell find $(CURRENT_PATH) -maxdepth 1 -type d)

SRC := $(foreach dir,$(DIRS),$(wildcard $(dir)/*.c))

OBJS :=$(patsubst %.c,%.o,$(SRC))

KO_NAME:=$(notdir $(CURRENT_PATH))_drv
#模块名，可以为一个系列，则编译成一些列的模块
obj-m:=$(KO_NAME).o
$(KO_NAME)-obj:=$(OBJS)

build:kernel_modules

kernel_modules:
	$(MAKE) -C $(KERNELDIR) M=$(CURRENT_PATH) modules
clean:
	$(MAKE) -C $(KERNELDIR) M=$(CURRENT_PATH) clean
	
.PHONY:build clean

#编译 ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-



