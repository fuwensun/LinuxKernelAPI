/*
linux/string.h
mm/util.c
void *kmemdup(const void *src, size_t len, gfp_t gfp)
复制内存块，地址src长度len，到以gfp方式新分配的内存。
*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/string.h>
#include <linux/gfp.h>
#include <linux/mm.h>

struct page *pages = NULL;

static int __init kmemdup_init(void){
	pages = alloc_pages(GFP_KERNEL,0);
	if(!pages){
		printk("alloc failed!\n");
		return -ENOMEM;
	}else{
		char *temp = NULL; 
		void *page_addr;
		int i = 0;
	
		page_addr = page_address(pages);//sfw** page -> address
		
		temp = (char *)page_addr;	
		for(*temp = 'a',i = 0; i < 26; i++){
			char x;
			x = *temp;
			temp++;
			*temp = x+1;
		}

		char *addr = kmemdup(page_addr,26,GFP_KERNEL);
		printk("addr = 0x%lx\n",(unsigned long)addr);
		printk("*addr = %c\n",*addr);
		printk("*addr+4= %c\n",*(addr+4));

		for(temp = addr; *temp != '\0';temp++)
			printk("%c",*temp);
	}

	return 0;
}

static void __exit kmemdup_exit(void){
	if(pages){
		__free_pages(pages,0);
	}
	printk("exit!\n");
}

module_init(kmemdup_init);
module_exit(kmemdup_exit);

MODULE_LICENSE("GPL");
