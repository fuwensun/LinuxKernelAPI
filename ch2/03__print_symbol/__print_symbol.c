/* linux/kernel/kallsyms.h
 * void __print_symbol(const char *fmt, unsigned long address)
 * 根据address打印内核符号信息，包括名、偏移、大小。信息一般是一个字符串，所以fmt通常含有“%s”
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kallsyms.h>

MODULE_LICENSE("GPL");

static int __init __print_symbol_init(void);
static void __exit __print_symbol_exit(void);

int a_symbol(void){
    return 1;
}

EXPORT_SYMBOL(a_symbol);

int __init __print_symbol_init(void){
    char *fmt = 0;
    unsigned long address = 0;
    char *name = 0;
    struct module *fmodule = NULL;

    address = (unsigned long) __builtin_return_address(0);		//sfw**当前函数地址
    fmt = "it's the first part,\n %s\n";
    __print_symbol(fmt,address);

    name = "vboxvideo";
    fmodule = find_module(name);

    if (fmodule){
        printk("fmodule->name: %s\n",fmodule->name);
        address = (unsigned long)fmodule->name;
        //address = (unsigned long)&fmodule->core_layout;
        fmt = "it's the second part,\n %s\n";
        __print_symbol(fmt, address);
    }
    
    address = (unsigned long)a_symbol+5;
    fmt = "it's the third part,\n %s\n";
    __print_symbol(fmt, address);

    return 0;

}

void __exit __print_symbol_exit(void){
    printk("module <%s> exit ok!\n",THIS_MODULE->name);
}

module_init(__print_symbol_init);
module_exit(__print_symbol_exit);
