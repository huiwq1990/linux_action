
multifile-y += main.o other.o src/test.o src/dirinclude.o src/searchinclude.o
obj-m += multifile.o
#generate the path
CURRENT_PATH:=$(shell pwd)
#the current kernel version number
LINUX_KERNEL:=$(shell uname -r)
#the absolute path
LINUX_KERNEL_PATH:=/usr/src/linux-headers-$(LINUX_KERNEL)
#complie object
all:
	make -C $(LINUX_KERNEL_PATH) EXTRA_CFLAGS=-I$(shell pwd)/include M=$(CURRENT_PATH) modules
#clean
clean:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) clean