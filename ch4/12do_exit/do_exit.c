/*
 *
 *
 */

#include <linux/module.h>
#include <linux/sched.h>
#include <linux/pid.h>
#include <linux/kernel.h>
#include <linux/kthread.h>

int my_function(void *argc){
	printk("-->in the kernel thread function now!\n");
	do_exit(0);
	printk("-->in the kernel thread function!\n");
	printk("-->the current pid is:%d\n",current->pid);
	printk("-->out the kernel thread function.\n");
	return 0;
}

static int __init do_exit_init(void){
	pid_t pidt = 0;
	struct task_struct *task = NULL;
	struct pid *kpid = NULL;

	printk("into do_eixt_init.\n");
	task = kthread_run(my_function,NULL,"XXX");
	kpid = get_task_pid(task,PIDTYPE_PID);
	pidt = pid_vnr(kpid);

	printk("the pid of get_task_pid is: %d\n",kpid->numbers[kpid->level].nr);
	printk("the pid of the kthread_run is: %d\n",pidt);
	printk("out do_exit_init.\n");
	return 0;
}

static void __exit do_exit_exit(void){
	printk("Goodbye do_exit\n");
}

module_init(do_exit_init);
module_exit(do_exit_exit);

MODULE_LICENSE("GPL");

