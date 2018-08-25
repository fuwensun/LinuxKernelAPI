/*
linux/gfp.h
mm/page_alloc.c
void free_pages(unsigned long addr, unsigned int order)
释放虚拟地址addr起2的order次方个物理页（页框/页帧）

unsigned long __get_free_pages(gfp_t gfp_mask, unsigned int order)
以gfpmask的方式申请2的order次方个物理页面，返回第一个页面的虚拟地址（线性地址）。
*/

#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/init.h>
#include <linux/gfp.h>


static unsigned long addr = 0;

static int __init __get_free_pages_init(void){
	printk("into __get_free_pages_init.\n");

	addr = __get_free_pages(GFP_KERNEL, 3);
	if(!addr){
		return -1;
	}else{
		printk("__get_free_pages Successfully!,\naddr = 0x%lx\n",addr);
	}
	printk("out __get_free_pages_init.\n");
	return 0;
}

static void __exit __get_free_pages_exit(void){
	if(addr){
		free_pages(addr,3);
		printk("free_pages ok!\n");
	}
	printk("exit!\n");
	return;
}

module_init(__get_free_pages_init);
module_exit(__get_free_pages_exit);

MODULE_LICENSE("GPL");
