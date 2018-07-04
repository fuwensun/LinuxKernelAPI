#include <linux/module.h>
#include <linux/init.h>
MODULE_LICENSE("GPL"); 
static int __init test_module_init(void); 
static void __exit test_module_exit(void);

int symbol_A(void)
{
	return 0;
}
int __init test_module_init(void) 
{ 
	printk("module <%s> init ok!\n",THIS_MODULE->name); 
	return 0; 
}

void __exit test_module_exit(void) 
{ 
	printk("module <%s> exit ok!\n",THIS_MODULE->name); 
}

EXPORT_SYMBOL(symbol_A);

module_init(test_module_init); 
module_exit(test_module_exit); 

