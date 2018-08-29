/*
linux/gfp.h
unsigned long get_zeroed_page(gfp_t gfp_mask)
在物理内存的线性映射区，以fgp，以fgp_mask的方式，mask的方式，获取一个页面。
成功返回页面的虚拟地址；失败返回0。
*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>

char *addr = NULL;

static int __init get_zeroed_page_init(void){

	addr = get_zeroed_page(GFP_KERNEL);
	if(!addr){
		printk("get_zeroed_page failed!\n");
	}else{
		printk("get_zeroed_page successfullly! addr = 0x%lx\n",(unsigned long)addr);
		printk("the content of addr+10 is: %d\n",*(addr+10));
		printk("the content of addr+1000 is: %d\n",*(addr+1000));
	}

	return 0;
}

static void __exit get_zeroed_page_exit(void){
	if(!addr){
		kfree(addr);
		printk("kfree ok!\n");
	}
	printk("exit!");
}

module_init(get_zeroed_page_init);
module_exit(get_zeroed_page_exit);

MODULE_LICENSE("GPL");
