/*
linux/slab.h
static inline void *kzalloc(size_t size, gfp_t flags)
以flags的方式分配size大小的清零的内存。
*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>

#define MEM_KZALLOC_SIZE 8092

char *mem_spvm = NULL;

static int __init kzalloc_init(void){
	
	mem_spvm = (char *)kzalloc(MEM_KZALLOC_SIZE,GFP_KERNEL);

	if(!mem_spvm){
		printk("kzalloc failed!\n");
	}else{
		printk("kzalloc successfully! addr = %lx\n",(unsigned long)mem_spvm);
		printk("the content of mem_spvm+2 is: %d\n",*(mem_spvm+2));
		printk("the content of mem_spvm+500 is: %d\n",*(mem_spvm+500));
	}
	return 0;
}

static void __exit kzalloc_exit(void){
	if(mem_spvm){
		kfree(mem_spvm);
		printk("kfree ok!\n");
	}
	printk("exit!\n");
	return;
}

module_init(kzalloc_init);
module_exit(kzalloc_exit);

MODULE_LICENSE("GPL");
