/*
linux/vmalloc.h
mm/vmalloc.c
struct vm_struct *__get_vm_area(unsigned long size, unsigned long flags,
				unsigned long start, unsigned long end);
以flags的方式从虚拟地址start到end的区间，获取size大小的虚拟内存。成功返回虚拟地址；失败返回NULL。
flags:
VM_ALLOC:通过vmalloc分配的页。
VM_MAP:通过vmap映射的已经分配的页。
VM_IOREMAP:通过ioremap映射的硬件设备的板上地址。

*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/vmalloc.h>
#include <linux/init.h>


static struct vm_struct *vm = NULL;

int __init __get_vm_area_init(void){
	vm = __get_vm_area(8192*4,VM_ALLOC,0xC0000100, 0xdd000000);
	if(!vm){
		return -ENOMEM;
	}else{
		printk("vm->size: %ld\n",vm->size);
		printk("vm->addr: 0x%lx\n",(unsigned long)vm->addr);
	}
	return 0;
}

void __exit __get_vm_area_exit(void){
	if(vm){
		free_vm_area(vm);
		printk("free_vm_area ok!\n");
	}
	printk("exit !\n");
	return;
}

module_init(__get_vm_area_init);
module_exit(__get_vm_area_exit);

MODULE_LICENSE("GPL");
