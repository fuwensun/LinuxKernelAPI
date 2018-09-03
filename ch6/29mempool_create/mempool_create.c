/*
linux/mempool.h
mm/mempool.c
mempool_t *mempool_create(int min_nr, mempool_alloc_t *alloc_fn,
				mempool_free_t *free_fn, void *pool_data)
sfw**  mempool_create - 创建一个内存池
@min_nr: 保证为该池分配的元素的最小数量
@alloc_fn: 用户定义的分配函数
@free_fn: 用户定义的释放函数
@pool_data: 可选的,传给用户定义的函数的,变量

这个函数创建并分配一个保证数量，预先分配的内存池。内存池可以用于  mempool_alloc() 和 
mempool_free() 函数。这个函数可能睡眠。alloc_fn() 和 free_fn() 函数可能睡眠 - 所以
mempool_alloc 函数不能在 IRQ 环境调用。

*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/mempool.h>

static struct kmem_cache *kmem = NULL;
static mempool_t *pool = NULL;

static int __init mempool_create_init(void){
	kmem = kmem_cache_create("my_buffer",10000,0,SLAB_HWCACHE_ALIGN,NULL);
	if(!kmem){
		printk("kmem_cache_create failed!\n");
		return 0;
	}
	printk("kmem_cache_create sccessfully!\n");
	pool = mempool_create(5,mempool_alloc_slab,mempool_free_slab,kmem);
	if(!pool){
		printk("mempool_create failed!\n");
		return 0;
	}
	printk("mempool_create scessfully! min_nr = %d\n",pool->min_nr);		
	return 0;
	
}

static void __exit mempool_create_exit(void){
	if(pool){
		mempool_destroy(pool);
		printk("mmepool_destroy succeed!\n");
	}
	if(kmem){
		kmem_cache_destroy(kmem);
		printk("kmem_cache_destroy succeed!\n");
	}
	printk("exit!\n");
} 

module_init(mempool_create_init);
module_exit(mempool_create_exit);

MODULE_LICENSE("GPL");
