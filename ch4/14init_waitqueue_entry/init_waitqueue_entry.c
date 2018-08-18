/*
*/

#include <linux/module.h>
#include <linux/sched.h>
#include <linux/list.h>
#include <linux/kthread.h>
#include <linux/pid.h>

int my_function(void *argc){
	printk("int the kernel thread function!\n");
	printk("the current pid is: %d\n",current->pid);
	printk("out the kernel thread function\n");
	return 0;
}

static int __init init_waitqueue_entry_init(void){
	struct task_struct *task = NULL;
	wait_queue_entry_t data;

	printk("into init_waitqueue_entry_init.\n");

	task = kthread_run(my_function,NULL,"XXX");

	if(data.private == NULL || data.func == NULL){
		printk("the data has not been initialized\n");
	}

	init_waitqueue_entry(&data,task);
	if(data.private == task && data.func != NULL){
		printk("the data has been initialized\n");
		printk("the flags of the data is: %d\n", data.flags);
	}
	else{
		printk("the data has not been initialized\n");
	}

	printk("the pidt of the kthread_run is: %d\n",task->pid);
	printk("the current pid is: %d\n",current->pid);
	printk("out init_waitqueue_entry_init.\n");
	return 0;
}

static void __exit init_waitqueue_entry_exit(void){
	printk("Goodbye init_waitqueue_entry\n");
}

module_init(init_waitqueue_entry_init);
module_exit(init_waitqueue_entry_exit);
MODULE_LICENSE("GPL");
