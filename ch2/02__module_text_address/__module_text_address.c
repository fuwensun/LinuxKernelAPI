/* 
 * linux/kernel/module.c
 * struct module *__module_text_address(unsigned long addr) 
 * 传入的地址(addr)如果是模块的代码段(text),返回module指针，否则返回NULL
 */

#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");

static int __init __module_text_address_init(void);
static void __exit __module_text_address_exit(void);

int fun_a(void){
    return 0;
}

static int var_b = 4;

int __init __module_text_address_init(void){

    unsigned long addr = 0;     
    struct module *ret = 0;

    addr = (unsigned long)fun_a;
    preempt_disable();
    ret = __module_text_address(addr);
    preempt_enable();

    printk("it's about fun_a:\n");
    if (ret != NULL){
        printk("ret->name: %s\n",ret->name);
        printk("ret->state: %d\n",ret->state);
        printk("ret->percpu_size: %d\n",ret->percpu_size);
    }else{
        printk("fun_a is not in text area!\n"); 
    }

    addr = (unsigned long)var_b;
    preempt_disable();
    ret = __module_text_address(addr);
    preempt_enable();

    printk("it's about var_b:\n");
    if (ret != NULL){
        printk("ret->name: %s\n",ret->name);
        printk("ret->state: %d\n",ret->state);
        printk("ret->percpu_size: %d\n",ret->percpu_size);
    }else{
        printk("var_b is not in text area!\n"); 
    }
    return 0;
}

void __exit __module_text_address_exit(void){
    printk(KERN_EMERG"module exit ok!\n");
}

module_init(__module_text_address_init);
module_exit(__module_text_address_exit);

