/*
linux/gfp.h
static inline struct page *alloc_pages(gfp_t gfp_mask, unsigned int order)
获取2的order次方个gfp_mask类型的连续的物理页，成功返回首页描述符地址，失败返回NULL。
*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/gfp.h>
#include <linux/mmzone.h>
#include <linux/mm.h>
#include <asm/page.h>


struct page *pages = NULL;

int __init alloc_pages_init(void){
	pages = alloc_pages(GFP_KERNEL,3);
	if(!pages){
		return -ENOMEM;
	}else{
		printk("alloc_pages Successfully!\n");
		printk("pages = 0x%lx\n",(unsigned long)pages);
//		printk("mem_map = 0x%lx\n",(unsigned long)mem_map);
//		printk("pages - mem_map = 0x%lx\n",(unsigned long)pages - (unsigned long)mem_map);
//		printk("(pages-mem_map)*4096 = 0x%lx\n",(unsigned long)(pages-mem_map)*4096);
		printk("page_address(pages) = 0x%lx\n",(unsigned long)page_address(pages));
	}
	return 0;
}

void __exit alloc_pages_exit(void){
	if(pages){
		__free_pages(pages,3);
		printk("__free_pages ok!\n");
	}
	printk("exit\n");
}

module_init(alloc_pages_init);
module_exit(alloc_pages_exit);

MODULE_LICENSE("GPL");
