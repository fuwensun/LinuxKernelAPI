
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/thread_info.h>

static int __init test_init(void){

	struct task_struct *t = NULL;
	struct thread_info *tf = NULL;

	t = current;
	tf = &t->thread_info;

	printk("addr of task_struct = 0x%p\n",(void*)t);
	printk("addr of thread_info = 0x%p\n",tf);
	
	printk("&task_struct == &thread_info, thread_info find task by itself task = &thread_info"); 

	printk("task kernel stack addr = 0x%p\n",t->stack);
	printk("size of thread_info = %d\n",sizeof(*tf));
	
	return 0;
}

static void __exit test_exit(void){
	return;
}

module_init(test_init);
module_exit(test_exit);
MODULE_LICENSE("GPL");
