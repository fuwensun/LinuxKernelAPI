/*
 * linux/sched.h
 * linux/kernel/pid.c
 * pid_t task_tgid_nr_ns(struct task_struct *task, struct pid_namespace *ns)
 * 根据task和ns获取进程号。
 */

#include <linux/module.h>
#include <linux/sched.h>
#include <linux/pid.h>
#include <linux/kthread.h>

int my_function(void *argc){
	printk("in the kernel thread function!\n");
	printk("the current pid is:%d\n",current->pid);
	return 0;
}

static int __init task_tgid_nr_ns_init(void){
	pid_t pidt = 0;
	pid_t pidt1 = 0;
	struct task_struct *task = NULL;
	struct pid *kpid = NULL;

	printk("into task_tgid_nr_ns_init.");
	task = kthread_run(my_function,NULL,"xxx");
	kpid = get_task_pid(task,PIDTYPE_PID);
	pidt = pid_nr(kpid);
	pidt1 = task_tgid_nr_ns(task,kpid->numbers[kpid->level].ns);

	printk("the pid of get_task_pid is:%d\n",kpid->numbers[kpid->level].nr);
	printk("the result of the task_tgid_nr_ns is:%d",pidt1);
	
	printk("the result of the kthread_run is:%d",pidt);
	printk("out task_tgid_nr_ns_init.\n");
	return 0;
}

static void __exit task_tgid_nr_ns_exit(void){
	printk("Goodbye task_tgid_nr_ns\n");
}

module_init(task_tgid_nr_ns_init);
module_exit(task_tgid_nr_ns_exit);

MODULE_LICENSE("GPL");

