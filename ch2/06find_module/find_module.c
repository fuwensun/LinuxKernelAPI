/*
 * linux/kernel/module.c
 * struct module *find_module(const char *name)
 * 如果模块名对应的模块存在，返回模块地址；否则返回NULL。
 */

#include <linux/module.h>
#include <linux/init.h>

static int __init find_module_init(void);
static void __exit find_module_exit(void);

int __init find_module_init(void){
    
    const char *name = 0;
    struct module *fmodule = NULL;

    name = "snd";
    fmodule = find_module(name);
    if (fmodule != NULL){
        printk("fmodule->name: %s\n",fmodule->name);
        printk("fmodule->state: %d\n",fmodule->state);
        printk("fmodule->precpu_size: %d\n",fmodule->percpu_size);
        printk("module_refcount(fmodule): %d\n",module_refcount(fmodule));
    }

    name = "soundcore";
    fmodule = find_module(name);
    if (fmodule != NULL){
        printk("fmodule->name: %s\n",fmodule->name);
        printk("fmodule->state: %d\n",fmodule->state);
        printk("fmodule->precpu_size: %d\n",fmodule->percpu_size);
        printk("module_refcount(fmodule): %d\n",module_refcount(fmodule));
    }


    return 0;
}

void __exit find_module_exit(void){
    printk("module <%s> exit ok!\n",THIS_MODULE->name);
}

module_init(find_module_init);
module_exit(find_module_exit);

MODULE_LICENSE("GPL");
