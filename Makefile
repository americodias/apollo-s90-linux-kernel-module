# Makefile for Apollo kernel module

ifneq ($(KERNELRELEASE),)

# Comment the following line to disable DEBUG
DEBUG := 1

obj-m := mod_apollo.o
mod_apollo-y =  chardev.o apollo.o module.o

EXTRA_CFLAGS += -I$(obj)
ifdef DEBUG
    EXTRA_CFLAGS += -D_DEBUG
endif

else
# Path to the kernel sources
# Adapt the path to your system setup
KDIR := /opt/ICnova_base/build_avr32/linux-2.6.24-icnova/

# Current directory
PWD  := $(shell pwd)

all:
	$(MAKE) -C $(KDIR) ARCH=avr32 CROSS_COMPILE=avr32-linux- SUBDIRS=$(PWD) modules

.PHONY: clean
clean:
	$(RM) *.o *~ *.ko
	
endif


