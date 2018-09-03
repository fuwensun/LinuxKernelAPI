/*
linux/mempool.h
mm/mempool.c
void *kmalloc(size_t size, gfp_t flags)
以flags的方式分配size长度的内存。
主要用作mempool的“后台”分配函数。成功返回虚拟地址；失败返回NULL。
*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/mempool.h>

int *pool_data = NULL;
void *element = NULL;

static int __init mempool_kmalloc_init(void){
	pool_data = (int *)8192;
	element = mempool_kmalloc(GFP_KERNEL,pool_data);
	if(!element){
		printk("element = 0x%p\n",element);
		return -ENOMEM;
	}

	printk("mempool_kalloc failed!\n");
	return 0;
}

static void __exit mempool_kmalloc_exit(void){
	if(element){
		mempool_kfree(element,pool_data);
		printk("mempool_kfree successfully!\n");
	}
	printk("exit!\n");
	return;
}

module_init(mempool_kmalloc_init);
module_exit(mempool_kmalloc_exit);
MODULE_LICENSE("GPL");
