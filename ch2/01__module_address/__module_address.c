/*
 * linux/kernel/module.c
 * struct module *__module_address(unsigned long add)
 * 根据内存地址add，获得地址所在的module
 */

#include<linux/module.h>
#include<linux/init.h>

MODULE_LICENSE("GPL");

static int __init __module_address_init(void);
static void __exit __module_address_exit(void);

int a_module(void){
	return 0;
}

struct module *ret = NULL;

int __init __module_address_init(void){

    unsigned long addr = (unsigned long)a_module;

    preempt_disable();
    ret = __module_address(addr);
    preempt_enable();

    if (!ret){
        printk(KERN_EMERG"__module_address return NULL!\n");
		return -ENOMEM;
    }

	printk(KERN_EMERG"ret->name: %s\n",ret->name);
    printk(KERN_EMERG"ret->state: %d\n",ret->state);
    printk(KERN_EMERG"ret->percpu_size: %d\n",ret->percpu_size);

    return 0;
}


void __exit __module_address_exit(void){
    
    printk(KERN_EMERG"ret->state: %d\n",ret->state);
    printk(KERN_EMERG"module exit ok!\n");
    printk(KERN_EMERG"ret->state: %d\n",ret->state);
	return;
}

module_init(__module_address_init);
module_exit(__module_address_exit);
