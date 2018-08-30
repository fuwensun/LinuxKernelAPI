/*
linux/slab.h
mm/slab_common.c
struct kmem_cache *kmem_cache_create(const char *name, unsigned int size, unsigned int align,slab_flags_t flags, void (*ctor)(void *))
name:缓存的名称，/proc/slabinfo中显示。
size：缓存创建的对象的大小，字节为单位。
align：对象对齐的方式。
flags：分配缓存的选项。
ctor：对象构造器，分配对象时回调。
*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>

char *mem_spvm = NULL;
struct kmem_cache *my_cachep = NULL;

static int __init kmem_cache_create_init(void){
	my_cachep = kmem_cache_create("my_cache", 32, 0, SLAB_HWCACHE_ALIGN, NULL);
	if(!my_cachep){
		printk("kmem_cache_create failed!\n");
	}else{
		printk("Cache size is: %d\n",kmem_cache_size(my_cachep));
		//printk("Cache name is: %s\n",kmem_cache_name(my_cachep));
	}
	return 0;
}

static void __exit kmem_cache_create_exit(void){
	if(my_cachep){
		kmem_cache_destroy(my_cachep);
		printk("kmem_cache_destroy successd!\n");
	}
	printk("exit!\n");
}

module_init(kmem_cache_create_init);
module_exit(kmem_cache_create_exit);

MODULE_LICENSE("GPL");
