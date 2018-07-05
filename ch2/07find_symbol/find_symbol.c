/*
 * linux/kernel/nodule.c
 * const struct kernel_symbol *find_symbol(const char *name,
 *                                          struct module **owner,
 *                                          const s32 **crc,
 *                                          bool gplok,
 *                                          bool warn)
 * name:要查找的符号的名字。
 * owner:二级指针，输出参数，指向符号所属的模块的地址。
 * crc:二级指针，输出参数，指向符号的crc值的地址。
 * golok:GPL符号ok？，1-ok，0-no。
 * warn:是否要输出警告消息。
 * 找到返回符号地址，否则返回NULL。
 */

#include <linux/module.h>
#include <linux/init.h>

static int __init find_symbol_init(void);
static void __exit find_symbol_exit(void);

int __init find_symbol_init(void){
    
    const char *name = NULL;
    const struct kernel_symbol *ksymbol = NULL;
    struct module *owner = NULL;
    const s32*crc = NULL;
    bool gplok = true;
    bool warn = true;
   
    name =  "symbol_A";
    gplok = true;
    warn = true;

    ksymbol = find_symbol(name,&owner,&crc,gplok,warn);
    printk("----%s----",name);
    if (ksymbol != NULL){
        printk("ksymbol->value: %lx\n",ksymbol->value);
        printk("ksymbol->name: %s\n",ksymbol->name);
    }else{
        printk("Failed to find symbol %s\n",name);
    }

    if (owner != NULL)
        printk("owner->name: %s\n",owner->name);

    if (crc != NULL)
        printk("*crc: %d\n", *crc);

    //----------- 
    name =  "symbol_A_GPL";
    gplok = true;
    warn = true;

    ksymbol = find_symbol(name,&owner,&crc,gplok,warn);
    printk("----%s----",name);
    if (ksymbol != NULL){
        printk("ksymbol->value: %lx\n",ksymbol->value);
        printk("ksymbol->name: %s\n",ksymbol->name);
    }else{
        printk("Failed to find symbol %s\n",name);
    }

    if (owner != NULL)
        printk("owner->name: %s\n",owner->name);

    if (crc != NULL)
        printk("*crc: %d\n", *crc);

   //----------- 
    name =  "symbol_A_GPL";
    gplok = false;
    warn = true;

    ksymbol = find_symbol(name,&owner,&crc,gplok,warn);
    printk("----%s----",name);
    if (ksymbol != NULL){
        printk("ksymbol->value: %lx\n",ksymbol->value);
        printk("ksymbol->name: %s\n",ksymbol->name);
    }else{
        printk("Failed to find symbol %s\n",name);
    }

    if (owner != NULL)
        printk("owner->name: %s\n",owner->name);

    if (crc != NULL)
        printk("*crc: %d\n", *crc);



    return 0;
}

void __exit find_symbol_exit(void){
    printk("module <%s> exit ok!\n",THIS_MODULE->name);
}
module_init(find_symbol_init);
module_exit(find_symbol_exit);

MODULE_LICENSE("GPL");
