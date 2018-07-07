/*
 * linux/kernel/module.c
 * usigned int module_refcount(struct module *mod)
 * 获得mod的引用计数
 */

#include <linux/module.h>
#include <linux/init.h>

static int __init module_refcount_init(void);
static void __exit module_refcount_exit(void);

int __init module_refcount_init(void){
	const char *name = "snd_seq_device";
	struct module *fmodule = find_module(name);

	if (fmodule != NULL){
		printk("fmodule->name: %s\n", fmodule->name);
		printk("module_refcount(fmodule): %d\n", module_refcount(fmodule));
	}
		
	printk("THIS_MODULE->name: %s\n", THIS_MODULE->name);
	printk("module_refcount(THIS_MODULE): %d\n", module_refcount(THIS_MODULE));
	return 0;
}

void __exit module_refcount_exit(void){
	printk("module <%s> exit ok!\n",THIS_MODULE->name);
}

module_init(module_refcount_init);
module_exit(module_refcount_exit);

MODULE_LICENSE("GPL");
