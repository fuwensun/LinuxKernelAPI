/*
*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

#define MEM_MALLOC_SIZE 4096
#define MEM_MAJOR	246	
#define MEM_MINOR	0

char *mem_spvm = NULL;
struct cdev *mem_cdev = NULL;

static int mem_open(struct inode *ind, struct file *filp);
static int mem_release(struct inode *ind, struct file *filp);
static ssize_t mem_read(struct file *filp, char __user *buf, size_t size, loff_t *fpos);
static ssize_t mem_write(struct file *filp, const char __user *buf, size_t size, loff_t *fpos);

struct file_operations mem_fops = {
	.open = mem_open,
	.release = mem_release,
	.read = mem_read,
	.write = mem_write,
};


static int mem_open(struct inode *ind, struct file *filp){
	printk("open vmalloc space!\n");
	try_module_get(THIS_MODULE);
	printk("open vmalloc space success\n");
	return 0;
}
static int mem_release(struct inode *ind, struct file *filp){
	printk("close vmalloc space\n");
	module_put(THIS_MODULE);
	printk("close vmalloc space success\n");
	return 0;
}
static ssize_t mem_read(struct file *filp, char __user *buf, size_t size, loff_t *fpos){

	int res = -1;
	char *tmp = NULL;
	printk("copy data to the user space!\n");
	tmp = mem_spvm;

	if(size > MEM_MALLOC_SIZE)
		size = MEM_MALLOC_SIZE;

	if(tmp){
		res = copy_to_user(buf,tmp,size);
	}

	if(res){
		printk("copy data fail to the user space\n");
		return -ENOMEM;
	}

	printk("copy data success and the data is: %s\n",tmp);
	return size;
}
static ssize_t mem_write(struct file *filp, const char __user *buf, size_t size, loff_t *fpos){

	int res = -1;
	char *tmp = NULL;
	printk("copy data to the user space!\n");
	tmp = mem_spvm;

	if(size > MEM_MALLOC_SIZE)
		size = MEM_MALLOC_SIZE;

	if(tmp){
		res = copy_from_user(tmp,buf,size);
	}

	if(res){
		printk("copy data fail to the user space\n");
		return -ENOMEM;
	}

	printk("copy data success and the data is: %s\n",tmp);
	return size;
}


static int __init cdev_add_del_init(void){
	int res = 0;
	int devno = 0;
	printk("into the cdev_add_del_init\n");

	devno = MKDEV(MEM_MAJOR,MEM_MINOR);
	mem_spvm = (char *)vmalloc(MEM_MALLOC_SIZE);
	if(!mem_spvm){
		printk("vmalloc failed!\n");
		return -ENOMEM;
	}
	printk("vmalloc successfully! addr = 0x%p\n",mem_spvm);

	mem_cdev = cdev_alloc();
	if(!mem_cdev){
		printk("cdev_alloc failed!\n");
		return -ENOMEM;
	}

	cdev_init(mem_cdev,&mem_fops);
	mem_cdev->owner = THIS_MODULE;
	kobject_set_name(&mem_cdev->kobj,"my_char_dev");
	res = cdev_add(mem_cdev,devno,1);
	if(res){
		printk("cdev add Error!\n");
		return res;
	}
	printk("cdev add ok! name = %s\n",mem_cdev->kobj.name);
	printk("out the cdev_add_del_init\n");
	return 0;
}

static void __exit cdev_add_del_exit(void){

	printk("into cdev_add_del_exit\n");
	if(mem_cdev){
		cdev_del(mem_cdev);
		printk("cdev del ok!\n");
	}
	if(mem_spvm){
		vfree(mem_spvm);
		printk("vfree ok!\n");
	}
	printk("out cdev_add_del_exit\n");
	return;
}

module_init(cdev_add_del_init);
module_exit(cdev_add_del_exit);

MODULE_LICENSE("GPL");
