/*
以gfplinux/mempool.h
mm/mempool.c
void *mempool_alloc_pages(gfp_t gfp_mask, void *pool_data);
以gfp_mask和pool_data为参数调用alloc_pages分配内存,
主要用作mempool的“后台”分配函数。成功返回虚拟地址；失败返回NULL。
*/


/*
 * A simple mempool-backed page allocator that allocates pages
 * of the order specified by pool_data.
 */
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/mempool.h>

int *pool_data;
void *element = NULL;

static int __init mempool_alloc_pages_init(void){
	pool_data = (int *)2;
	element = mempool_alloc_pages(GFP_KERNEL,pool_data);
	
	if(element){
		printk("element = 0x%p\n",element);
	}else{
		printk("mempool_alloc_pages failed\n");
	}
	return 0;
}

static void __exit mempool_alloc_pages_exit(void){
	if(element){
		mempool_free_pages(element,pool_data);
		printk("mempool_free_pages sucessfully!\n");
	}
	printk("exit!\n");
}

module_init(mempool_alloc_pages_init);
module_exit(mempool_alloc_pages_exit);

MODULE_LICENSE("GPL");
