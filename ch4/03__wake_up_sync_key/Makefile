ifneq ($(KERNELRELEASE),)         #第二次make执行路径，KERNELRELEASE内核源码Makefile中定义的变量，第一次make（手动）时，未定义

obj-m += __wake_up_sync_key.o

else                              #第一次make执行路径            

PWD := $(shell pwd)
KVER := $(shell uname -r)
KDIR := /lib/modules/$(KVER)/build

all:
	$(MAKE) -C $(KDIR) M=$(PWD)   #第二次make，读取KDIR中的Makefile（读到KERNELRELEASE定义），然后返回PWD，此时KERNELRELEASE已定义   
clean:
	rm -rf *.o *.mod.c *.ko *.symvers *.order *.markers *~

endif
