/*

*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/vmalloc.h>
#include <linux/slab.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/device.h>
#define MEM_MALLOC_SIZE 4096
#define MEM_MAJOR	0	
#define MEM_MINOR	10

char *mem_spvm = NULL;
struct class *mem_class = NULL;

static int mem_open(struct inode *ind, struct file *filp);
static int mem_release(struct inode *ind, struct file *filp);
static ssize_t mem_read(struct file *filp, char __user *buf,size_t size, loff_t *fpos);
static ssize_t mem_write(struct file *filp, const char __user *buf, size_t size, loff_t *fpos);
static void class_create_release(struct class *cls);

struct file_operations mem_fops = {
	.owner = THIS_MODULE,
	.open = mem_open,
	.release = mem_release,
	.read = mem_read,
	.write = mem_write,
};

static int __init class_register_unregister_init(void){
	int res = -1;
	int ret = 0;
	printk("into class_register_unregister_init\n");
	
	//alloc-register-dev
	mem_spvm = (char *)vmalloc(MEM_MALLOC_SIZE);
	res = register_chrdev(MEM_MAJOR,"my_char_dev",&mem_fops);
	if(res < 0){						// <----- failed  res < 0	
		//unregister_chrdev(MEM_MAJOR,"my_char_dev");
		printk("register char dev failed <E 1> ,res = %d\n",res);
		return -ENOMEM;
	}
	printk("register char dev success [S 1]\n");

	//alloc-register-class
	mem_class = kzalloc(sizeof(*mem_class),GFP_KERNEL);
	if(!mem_class){
		kfree(mem_class);
		printk("failed in kzalloc class <E 2>\n");
		return -ENOMEM;
	}
	printk("kzalloc class success [S 2]\n");
	mem_class->name = "my_char_dev_class";
	mem_class->owner = THIS_MODULE;
	mem_class->class_release = class_create_release;
	
	ret = class_register(mem_class);
	//struct lock_class_key key;
	//ret = __class_register(mem_class,&key);
	if(ret){
		kfree(mem_class);
		printk("failed in registing class <E 3>\n");
		return -ENOMEM;
	}
	printk("register class success [S 3]\n");
	
	//dev-to-clase-dir
	device_create(mem_class,NULL,MKDEV(MEM_MAJOR,MEM_MINOR),NULL,"my_char_dev__IN__class");
	printk("device create success [S 4]\n");
	printk("out class_register_unregister_init\n");
	return 0;
}

static void __exit class_register_unregister_exit(void){
	
	printk("into class_register_unregister_exit\n");
	unregister_chrdev(MEM_MAJOR,"my_char_dev");
	device_destroy(mem_class,MKDEV(MEM_MAJOR,MEM_MINOR));
	if((mem_class) && (!IS_ERR(mem_class)))
		class_unregister(mem_class);
	if(mem_spvm)
		vfree(mem_spvm);
	printk("vfree ok!\n");
	printk("out class_register_unregister_exit\n");
	return;
}

module_init(class_register_unregister_init);
module_exit(class_register_unregister_exit);
MODULE_LICENSE("GPL");

int mem_open(struct inode *ind, struct file *filp){
	printk("open vmalloc space\n");
	try_module_get(THIS_MODULE);
	printk("open vmalloc space success\n");
	return 0;
}



ssize_t mem_read(struct file *filp, char __user *buf, size_t size, loff_t *fpos){
	int res = -1;
	char *tmp = NULL;
	printk("copy data to the user space\n");
	tmp = mem_spvm;
	if(size > MEM_MALLOC_SIZE)
		size = MEM_MALLOC_SIZE;
	if(!tmp){
		res = copy_to_user(buf,tmp,size);
	}
	if(!res){
		printk("copy data success and the data is: %s\n",tmp);
		return size;
	}else{
		printk("copy data fail to the user space\n");
		return 0;
	}
}


ssize_t mem_write(struct file *filp, const char __user *buf, size_t size, loff_t *fpos){
	int res = -1;
	char *tmp = NULL;
	
	printk("read data from the user space\n");
	tmp = mem_spvm;
	if(size > MEM_MALLOC_SIZE)
		size = MEM_MALLOC_SIZE;
	if(!tmp){
		res = copy_from_user(tmp,buf,size);
		return size;
	}else{
		printk("read data from user space fail\n");
		return 0;
	}
}

int mem_release(struct inode *ind, struct file *filp){
	printk("close vmlloc space\n");
	module_put(THIS_MODULE);
	printk("close vmalloc space success\n");
	return 0;
}

void class_create_release(struct class *cls){
	pr_debug("%s called for %s\n",__func__, cls->name);
	kfree(cls);
}



