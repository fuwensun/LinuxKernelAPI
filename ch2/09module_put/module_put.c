/*
 * linux/kernel/module.c
 * void module_put(struct module *module)
 * 将module的引用计数减一 
 */

#include <linux/module.h>
#include <linux/init.h>

static int __init module_put_init(void);
static void __exit module_put_exit(void);

int __init module_put_init(void){
	const char *name = "test_module";
	struct module *fmodule = find_module(name);
	if (fmodule == NULL){
		printk("find %s failed!", name);
		return 0;
	}
	
	if (!module_refcount(fmodule)){
		if (!try_module_get(fmodule)){
			printk("can't get module!\n");
			return 0;
		}
	}

	printk("before calling module_put,\n");
	printk("refs of %s is: %d\n",name,module_refcount(fmodule));

	module_put(fmodule);

	printk("after calling module_put,\n");
	printk("refs of %s is: %d\n",name,module_refcount(fmodule));
	return 0;
}

void __exit module_put_exit(void){
	printk("module <%s> exit ok!\n",THIS_MODULE->name);
}

module_init(module_put_init);
module_exit(module_put_exit);

MODULE_LICENSE("GPL");
