/*
 * linux/pid_namespace.h
 * linux/kernel/pid.c
 * struct pid_namespace *task_active_pid_ns(struct task_struct *task)
 * 获取task对应的命名空间。
 */

#include <linux/module.h>
#include <linux/sched.h>
#include <linux/pid.h>
#include <linux/kthread.h>
#include <linux/pid_namespace.h>

int my_function(void *argc){
	printk("in the kernel thread function!\n");
	printk("the current pid is:%d\n",current->pid);
	return 0;
}

static int __init task_active_pid_ns_init(void){
	pid_t pidt = 0;
	struct task_struct *task = NULL;
	struct pid *kpid = NULL;
	struct pid_namespace *ns = NULL;

	printk("into task_active_pid_ns_init.\n");
	task = kthread_run(my_function,NULL,"xxx");
	kpid = get_task_pid(task,PIDTYPE_PID);
	ns = task_active_pid_ns(task);
	pidt = pid_nr(kpid);

	printk("the pidt of the pid_nr is:%d",kpid->numbers[kpid->level].nr);
	printk("the hide_pid of the task_active_pid_ns result is:%d\n",ns->hide_pid);
	printk("the pidt of the kthread_run is:%d", pidt);

	printk("out task_active_pid_ns_init.\n");
	return 0;
}

static void __exit task_active_pid_ns_exit(void){
	printk("Goodbye task_active_pid_ns\n");
}

module_init(task_active_pid_ns_init);
module_exit(task_active_pid_ns_exit);

MODULE_LICENSE("GPL");

