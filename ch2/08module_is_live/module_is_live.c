/*
 * linux/include/linux/module.h
 * static inline int module_is_live(struct module *mod)
 * 如果mod是live（no going），返回1，否则返回0。 
 */

#include <linux/module.h>
#include <linux/init.h>

static int __init module_is_live_init(void);
static void __exit module_is_live_exit(void);

static int ret = 0;

int __init module_is_live_init(void){
   ret = module_is_live(THIS_MODULE);

   if (ret == 1){
		printk("in init, state is: not GOING!\n");
   }else{
		printk("in init, state is: GOING\n");
   }
   return 0;
}

void __exit module_is_live_exit(void){
   ret = module_is_live(THIS_MODULE);

   if (ret == 1){
		printk("in exit, state is: not GOING!\n");
   }else{
		printk("in exit, state is: GOING\n");
   }
 
	printk("module <%s> exit ok!\n",THIS_MODULE->name);
}

module_init(module_is_live_init);
module_exit(module_is_live_exit);
