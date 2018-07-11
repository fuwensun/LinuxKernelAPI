/*
 * linux/pid.h
 * linux/kernel/pid.c
 * stuct pid *find_vpid(pid_t nr)
 * 根据进程对应的局部进程号（一般和进程号相同）返回pid，否则返回NULL。 
 */

#include <linux/module.h>
#include <linux/sched.h>
#include <linux/pid.h>
#include <linux/kthread.h>

int my_function(void *argc){
	printk("in the kernel thread function!\n");
	return 0;
}

static int __init get_pid_init(void){
	int result = 0;
	struct pid *vpid = NULL;
	struct pid *mpid = NULL;
	struct task_struct *task = NULL;

	printk("into find_vpid_init.\n");

	task = kthread_run(my_function,NULL,"XXX");
	result = task->pid;
	vpid = find_vpid(result);

	printk("the count of the pid is: %d\n",vpid->count);
	printk("the level of the pid is: %d\n",vpid->level);
	
	mpid = get_pid(vpid);
	printk("the count of the mpid is: %d\n",mpid->count);
	printk("the level of the mpid is: %d\n",mpid->level);
			
	printk("out find_vpid_init.\n");

	return 0;

}

static void __exit get_pid_exit(void){
	printk("Goodbye find_vpid\n");
}

module_init(get_pid_init);
module_exit(get_pid_exit);

MODULE_LICENSE("GPL");
