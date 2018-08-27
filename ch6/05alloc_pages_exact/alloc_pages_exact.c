/*
linux/gfp.h
void *alloc_pages_exact(size_t size, gfp_t gfp_mask)
页对齐的方式获取size大小gfp_mask类型的连续的物理页，成功返回首页线性地址，失败返回NULL。
*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/gfp.h>
#include <linux/mmzone.h>
#include <linux/mm.h>
#include <asm/page.h>

#define size 8092
void *addr = NULL;

int __init alloc_pages_exact_init(void){
	addr = alloc_pages_exact(size,GFP_KERNEL);
	if(!addr){
		return -ENOMEM;
	}else{
		printk("alloc_pages_exact Successfully!\n");
		printk("pages = 0x%lx\n",(unsigned long)addr);
	}
	return 0;
}

void __exit alloc_pages_exact_exit(void){
	if(addr){
		free_pages_exact(addr,size);
		printk("__free_pages_exact ok!\n");
	}
	printk("exit\n");
}

module_init(alloc_pages_exact_init);
module_exit(alloc_pages_exact_exit);

MODULE_LICENSE("GPL");
