/*
linux/slab.h
mm/slab.c
size_t ksize(const void *objp)
获取 kmalloc() 和 kmem_cache_alloc() 分配的内存空间的实际大小。
*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>

struct kmem_cache *my_cachep = NULL;
void *object1 = NULL;
void *object2 = NULL;

static int __init ksize_init(void){
	my_cachep = kmem_cache_create("my_cache",29,0,SLAB_HWCACHE_ALIGN,NULL);
	
	if(!my_cachep){
		printk("kmem_cache_create failed!\n");
	}else{
		object1 = kmem_cache_alloc(my_cachep,GFP_KERNEL);
		if(!object1){
			printk("kmem_cache_alloc failed!\n");
		}else{
			printk("the actual amount of memory allocated for object1 is: %ld\n",ksize(object1));
		}

		object2 = kmalloc(8080,GFP_KERNEL);
		if(!object2){
			printk("kmalloc failed!\n");
		}else{
			printk("the actual amount of memory allocated for a object2 is: %ld\n",ksize(object2));
		}
	}
	return 0;
}

static void __exit ksize_exit(void){
	if(object1){
		kmem_cache_free(my_cachep,object1);
		printk("free object1 successfully!\n");
	}

	if(object2){
		kfree(object2);
		printk("free object2 successfully!\n");
	}

	if(my_cachep){
		kmem_cache_destroy(my_cachep);
		printk("destory my_cachep successfully!\n");
	}

	printk("exit!\n");
}

module_init(ksize_init);
module_exit(ksize_exit);

MODULE_LICENSE("GPL");

