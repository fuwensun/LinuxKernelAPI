/*
linux/slab.h
static __always_inline void *kmalloc(size_t size, gfp_t flags)
以flags的方式分配size虚拟内存，成功返回虚拟地址；失败返回NULL。
*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>

#define MEM_ALLOC_SIZE 8192
char *mem_spvm = NULL;

static int __init kcalloc_init(void){
	
	mem_spvm = (char *)kcalloc(2,MEM_ALLOC_SIZE,GFP_KERNEL);
	if(!mem_spvm){
		printk("kcalloc failed!\n");
	}else{
		printk("kcalloc successfullly! addr = 0x%lx\n",(unsigned long)mem_spvm);
		printk("the actual allocatied size is: %d\n",(unsigned int)ksize(mem_spvm));//sfw** ksize()
		printk("the content of mem_spvm+10 is: %d\n",*(mem_spvm+10));
		printk("the content of mem_spvm+1000 is: %d\n",*(mem_spvm+1000));
	}

	return 0;
}

static void __exit kcalloc_exit(void){
	if(!mem_spvm){
		kfree(mem_spvm);
		printk("kfree ok!\n");
	}
	printk("exit!");
}

module_init(kcalloc_init);
module_exit(kcalloc_exit);

MODULE_LICENSE("GPL");
