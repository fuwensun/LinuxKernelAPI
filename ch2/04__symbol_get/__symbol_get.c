/*
 *linux/kernel/module.c
 *void __symbol_get(const char *symbol)
 *如果符号存在，返回地址，引用计数加一；否则返回NULL
 */

#include <linux/module.h>
#include <linux/init.h>

static int __init __symbol_get_init(void);
static void __exit __symbol_get_exit(void);

int __init __symbol_get_init(void){
    const char *symbol_name = 0;
    void *addr = 0;

    symbol_name = "cpu_info";
    addr = __symbol_get(symbol_name);

    if (addr){
        printk("the address of %s is: %lx\n",symbol_name,(unsigned long)addr);
    }else{
        printk("%s isn't found\n",symbol_name);
    }

    symbol_name = "symbol_0";
    addr = __symbol_get(symbol_name);

    if (addr){
        printk("the address of %s is: %lx\n",symbol_name,(unsigned long)addr);
    }else{
        printk("%s isn't found\n",symbol_name);
    }

    return 0;
}

void __exit __symbol_get_exit(void){
    printk("module <%s> exit ok!\n",THIS_MODULE->name);
}

module_init(__symbol_get_init);
module_exit(__symbol_get_exit);

MODULE_LICENSE("GPL");
