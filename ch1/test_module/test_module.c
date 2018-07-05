#include <linux/module.h>
#include <linux/init.h>

static int __init test_module_init(void); 
static void __exit test_module_exit(void);

int symbol_A(void)
{
	return 0;
}
int symbol_A_GPL(void)
{
	return 0;
}

int symbol_A_GPL_FUTURE(void)
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
EXPORT_SYMBOL_GPL(symbol_A_GPL);
EXPORT_SYMBOL_GPL_FUTURE(symbol_A_GPL_FUTURE);

MODULE_LICENSE("GPL"); 

module_init(test_module_init); 
module_exit(test_module_exit); 

