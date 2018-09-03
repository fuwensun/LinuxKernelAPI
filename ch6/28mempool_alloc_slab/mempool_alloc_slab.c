/*
linux/mempool.h
mm/mempool.c
void *mempool_alloc_slab(gfp_t gfp_mask, void *pool_data)
以gfp_mask的方式从高速缓存pool_data中分配一个元素。
主要用作mempool的“后台”分配函数。成功返回虚拟地址；失败返回NULL。
*/
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/mempool.h>
#include <linux/slab.h>

static struct kmem_cache *kmem = NULL;
void *element = NULL;

static int __init mempool_alloc_slab_init(void){
	
	kmem = kmem_cache_create("my_buffer",10000,0,SLAB_HWCACHE_ALIGN,NULL);
	if(!kmem){
		printk("kmem_cache_create failed!\n");
		return 0;
	}else{
		printk("kmem_cache_create successfully!\n");

		element = mempool_alloc_slab(GFP_KERNEL,kmem);
		printk("element = 0x%p\n",element);
	}
	return 0;

}

static void __exit mempool_alloc_slab_exit(void){
	if(element){
		mempool_free_slab(element,kmem);
		printk("mempool_free_slab successfully!\n");
	}
	if(kmem){
		kmem_cache_destroy(kmem);
		printk("kmem_cache_destroy successfully!\n");
	}
	printk("exit!\n");
}

module_init(mempool_alloc_slab_init);
module_exit(mempool_alloc_slab_exit);

MODULE_LICENSE("GPL");
