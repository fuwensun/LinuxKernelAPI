/*
 * linux/pid.h
 * static inline struct pid_namespace *ns_of_pid(struct pid *pid)
 * 根据进程描述符获得其命名空间。
 */

#include <linux/module.h>
#include <linux/sched.h>
#include <linux/pid.h>
#include <linux/pid_namespace.h>
#include <linux/kthread.h>



int my_function(void *argc){
	printk("in the kernel thread function\n");
	printk("the current pid is:%d\n",current->pid);
	printk("the current tpid is:%d\n",current->tgid);
	return 0;
}

static int __init ns_of_pid_init(void){
	int result = 0;
	struct task_struct *task = NULL;
	struct pid *kpid = NULL;
	struct pid_namespace *pid_ns = NULL;

	printk("into ns_of_init.\n");
	task = kthread_run(my_function,NULL,"xxx");
	kpid = get_task_pid(task,PIDTYPE_PID);
	result = pid_vnr(kpid);

	printk("the level of the pid is:%d\n",kpid->level);
	printk("the pid of the pid is:%d\n",kpid->numbers[kpid->level].nr);

	pid_ns = ns_of_pid(kpid);
	printk("the level of the pid_namespace is:%d\n",pid_ns->level);
	printk("the last_pid of pid_namespace is:%d\n",pid_ns->hide_pid);
	printk("the kthread_run result is:%d\n",result);
	printk("the current pid is:%d\n",current->pid);
	printk("the current tgid is:%d\n",current->tgid);

	printk("outto ns_of_init.\n");
	return 0;
}

static void __exit ns_of_pid_exit(void){
	printk("Goodbye ns_of_pid\n");
}

module_init(ns_of_pid_init);
module_exit(ns_of_pid_exit);

MODULE_LICENSE("GPL");
