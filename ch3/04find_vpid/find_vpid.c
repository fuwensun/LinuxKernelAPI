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

static int __init find_task_by_pid_ns_init(void){
	int result = 0;
	struct pid *vpid = NULL;
	struct task_struct *task = NULL;

	printk("into find_vpid_init.\n");

	task = kthread_run(my_function,NULL,"XXX");
	result = task->pid;
	vpid = find_vpid(result);

	printk("the count of the pid is: %d\n",vpid->count);
	printk("the level of the pid is: %d\n",vpid->level);

	printk("the pid of the find_vpid is :%d\n",vpid->numbers[vpid->level].nr);

	printk("the result of the kthread_run is:%d\n",result);
	printk("out find_vpid_init.\n");

	return 0;

}

static void __exit find_task_by_pid_ns_exit(void){
	printk("Goodbye find_vpid\n");
}

module_init(find_task_by_pid_ns_init);
module_exit(find_task_by_pid_ns_exit);

MODULE_LICENSE("GPL");
