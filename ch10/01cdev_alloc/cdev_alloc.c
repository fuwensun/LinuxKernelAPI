/*
linux/cdev.h
fs/char_dev.c
struct cdev *cdev_alloc(void)
分配一个 struct cdev 结构体，成功返回结构体指针；失败返回NULL。
*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/slab.h>

struct cdev *mem_cdev;

static int __init cdev_alloc_init(void){
	printk("into the cdev_alloc_init\n");
	mem_cdev = cdev_alloc();
	if(!mem_cdev){
		printk("cdev_alloc failed!\n");
	}
	printk("cdev_alloc success! addr = 0x%p\n",mem_cdev);

	if(!&(mem_cdev->list)){
		printk("the list_head of the mem_dev has been initialized\n");
	}
	if(!&(mem_cdev->kobj)){
		printk("the kobj of the mem_dev has been initialized\n");
		printk("the state_in_sysfs of the kobj of the mem_cdev is: %d\n",mem_cdev->kobj.state_in_sysfs);
		printk("the state_initialized of teh kobj of the mem_cdev is: %d\n",mem_cdev->kobj.state_initialized);

	}
	printk("out the cdev_alloc_init\n");
	return 0;
}

static void __exit cdev_alloc_exit(void){
	printk("into cdev_alloc_exit\n");
	if(mem_cdev){
		kfree(mem_cdev);
	}
	printk("kfree mem_cdev ok!\n");
	printk("out cdev_alloc_exit\n");
	return;
}

module_init(cdev_alloc_init);
module_exit(cdev_alloc_exit);

MODULE_LICENSE("GPL");

