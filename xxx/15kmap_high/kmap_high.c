/*
linux/slab.h
static __always_inline void *kmalloc(size_t size, gfp_t flags)
以flags的方式分配size虚拟内存，成功返回虚拟地址；失败返回NULL。
*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/mm.h>
#include <asm/highmem.h>

struct page *pages = NULL;

static int __init kmap_high_init(void){

	pages = alloc_pages(__GFP_HIGHMEM,0);
	if(!pages){
		return -ENOMEM;
	}else{
		printk("kcalloc successfullly! pages= 0x%lx\n",(unsigned long)pages);
		void *addr = kmap_high(pages);
		printk("addr = 0x%lx\n",(unsigned long)addr);
	}

	return 0;
}

static void __exit kmap_high_exit(void){
	if(pages){
		kunmap_high(pages);
		printk("kunmap_high successd!\n");
		__free_pages(pages,0);
		printk("__free_pages ok!\n");
	}
	printk("exit!");
}

module_init(kmap_high_init);
module_exit(kmap_high_exit);

//MODULE_LICENSE("GPL");
