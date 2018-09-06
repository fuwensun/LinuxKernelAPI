/*

*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/device.h>

static struct class *mem_class = NULL;

static int __init class_create_destroy_init(void){
	
	struct lock_class_key key;

	printk("into the class_create_destroy_init\n");
	mem_class = class_create(THIS_MODULE,"my_char_class");
	//mem_class = __class_create(THIS_MODULE,"my_char_class",&key);

	if(IS_ERR(mem_class)){
		printk("err: failed in creating class.\n");
		return -ENOMEM;
	}
	
	printk("class create success\n");
	printk("out the class_create_destroy_init\n");
	return 0;
	
}

static void __exit class_create_destroy_exit(void){
	printk("into class_create_destroy_exit\n");
	if(mem_class){
		class_destroy(mem_class);
		printk("the mem_class has been destroyed\n");
	}
	printk("out class_create_destroy_exit\n");
}

module_init(class_create_destroy_init);
module_exit(class_create_destroy_exit);

MODULE_LICENSE("GPL");
