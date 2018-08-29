/*
linux/slab.h
mm/slab.c
void *kmem_cache_alloc(struct kmem_cache *cachep, gfp_t flags)
以flags的方式从给定缓存cachep分配一个对象。
*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>

struct kmem_cache *my_cachep = NULL;
void *object = NULL;

static int __init kmem_cache_alloc_init(void){
	my_cachep = kmem_cache_create("my_cache",35,0,SLAB_HWCACHE_ALIGN,NULL);
	if(!my_cachep){
		printk("kmem_cache_create failed!\n");
	}else{
		object = kmem_cache_alloc(my_cachep,GFP_KERNEL);
		if(!object){
			printk("kmem_cache_alloc failed!\n");
		}else{
			printk("allocate object is 0x%lx\n",(unsigned long)object);
		}
	}
	return 0;
}

static void __exit kmem_cache_alloc_exit(void){
	if(object){
		kmem_cache_free(my_cachep,object);
		printk("free object successfully!\n");
	}

	if(my_cachep){
		kmem_cache_destroy(my_cachep);
		printk("destroy my_cachep successfully!");
	}
	printk("exit!\n");
	return;
}

module_init(kmem_cache_alloc_init);
module_exit(kmem_cache_alloc_exit);

MODULE_LICENSE("GPL");
