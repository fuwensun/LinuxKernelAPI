/*
*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>


static int mem_open(struct inode *ind, struct file *filp){
	return 0;
}
static int mem_release(struct inode *ind, struct file *filp){
	return 0;
}
static ssize_t mem_read(struct file *filp, char __user *buf, size_t size, loff_t *fpos){
	return 10;
}
static ssize_t mem_write(struct file *filp, const char __user *buf, size_t size, loff_t *fpos){
	return 10;
}


struct file_operations mem_fops = {
	.open = mem_open,
	.release = mem_release,
	.read = mem_read,
	.write = mem_write,
};

struct cdev *mem_cdev = NULL;

static int __init cdev_init_init(void){
	printk("into the cdev_init_init\n");

	mem_cdev = cdev_alloc();
	if(!mem_cdev){
		printk("cdev_alloc failed!\n");
		return -ENOMEM;
	}

	if(!mem_cdev->ops){
		printk("the ops of the mem_dev has not been init!\n");
	}else{
		printk("the ops of the mem_dev has been init!\n");
	}

	cdev_init(mem_cdev,&mem_fops);
	
	if(!mem_cdev->ops){
		printk("the ops of the mem_dev has not been init!\n");
	}else{
		printk("the ops of the mem_dev has been init!\n");
	}

	printk("out the cdev_init_init\n");
	return 0;
}

static void __exit cdev_init_exit(void){

	printk("into cdev_init_exit\n");
	if(mem_cdev){
		cdev_del(mem_cdev);
		printk("cdev del ok!\n");
	}
	printk("out cdev_init_exit\n");
}

module_init(cdev_init_init);
module_exit(cdev_init_exit);

MODULE_LICENSE("GPL");
