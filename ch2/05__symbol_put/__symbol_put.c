/* linux/kernel/module.c
 * void __symbol_put(const char *symbol)
 * 如果符号存在，其所在模块引用减一，无返回值
 */
 
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>

static int __init __symbol_put_init(void);
static void __exit __symbol_put_exit(void);

int __init __symbol_put_init(void){
    	const char *symbol_name = NULL;
    	const char *mod_name = NULL;
    	struct module *fmodule = NULL;

    	symbol_name = "symbol_A";
    	//symbol_name = "start_kernel";
    	mod_name = "test_module";
    	//mod_name = "ip_tables";
    	fmodule = find_module(mod_name);
   	if (!fmodule){
        	printk("find %s failed!\n", mod_name);
		return 0;
    	}

	if (!try_module_get(fmodule)){
           	printk("get moudle failed!\n");
            	return 0;
        }
        printk("before calling _symbol_get,__symbol_put,\n");
        printk("ref of %s is: %d\n",mod_name,module_refcount(fmodule));
        __symbol_get(symbol_name);  //此处确认__symbol_get增加symbol_name所在module的ref                                    
        printk("after calling __symbol_get,\n");
        printk("ref of %s is: %d\n",mod_name,module_refcount(fmodule));
        __symbol_put(symbol_name);
        printk("after calling __symbol_put,\n");
        printk("ref of %s is: %d\n",mod_name,module_refcount(fmodule));
 
        module_put(fmodule);
    
	return 0;
}

void __exit __symbol_put_exit(void){
    	printk("module <%s> exit ok!\n",THIS_MODULE->name);
}

module_init(__symbol_put_init);
module_exit(__symbol_put_exit);

MODULE_LICENSE("GPL");
