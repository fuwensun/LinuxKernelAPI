/*
linux/mempool.h
mm/mempool.c
void *mempool_alloc(mempool_t *pool, gfp_t gfp_mask)
以gfpmask方式从内存池pool分配一个元素。
函数只有当allocfn函数睡眠时才睡眠，成功返回地址；失败返回NULL。
因为预先分配，在进程环境不会失败；在 IRQ 可能失败。
*/
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/mempool.h>

static struct kmem_cache *kmem = NULL;
static mempool_t *pool = NULL;
static void *element = NULL;

static int __init mempool_alloc_init(void){

	kmem = kmem_cache_create("my_buffer",1000,0,SLAB_HWCACHE_ALIGN,NULL);
	if(!kmem){
		printk("kmem_cache_create failed!\n");
		return -ENOMEM;
	}
	printk("kmem_cache_create sucessfully! kmem = 0x%p\n",kmem);

	pool = mempool_create(5,mempool_alloc_slab,mempool_free_slab,kmem);
	if(!pool){
		printk("mempool_create failed!\n");
		return -ENOMEM;
	}
	printk("mempool_create sucessfully1 min_nr = %d\n",pool->min_nr);

	element = mempool_alloc(pool,GFP_KERNEL);
	printk("after mempool_alloc,element = 0x%p\n",(void *)element);
	
	return 0;
}

static void __exit mempool_alloc_exit(void){
	
	if(element){
		mempool_free(element,pool);
		printk("mempool_free sucessfully!\n");
	}

	if(pool){
		mempool_destroy(pool);
		printk("mempool_destroy sucessfully!\n");
	}

	if(kmem){
		kmem_cache_destroy(kmem);
		printk("kmem_cache_destroy sucessfully1\n");
	}
	printk("exit!\n");
	return;
}

module_init(mempool_alloc_init);
module_exit(mempool_alloc_exit);

MODULE_LICENSE("GPL");
