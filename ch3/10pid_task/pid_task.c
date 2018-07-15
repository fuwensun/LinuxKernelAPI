/*
 * linux/pid.h
 * struct task_struct *pid_task(struct pid *pid, enum pid_type)
 * 根据进程描述符和其类型获得进程结构体。
 */

#include <linux/module.h>
#include <linux/sched.h>
#include <linux/pid.h>
#include <linux/kthread.h>

int my_function(void *argc){
	printk("in the kernel thread function!\n");
	return 0;
}

static int __init pid_task_init(void){
	int result = 0;
	struct task_struct *task = NULL;
	struct pid *kpid = NULL;
	
	printk("into the pid_task_init.\n");
	task = kthread_run(my_function,NULL,"xxx");
	kpid = get_task_pid(task,PIDTYPE_PID);
	task = pid_task(kpid,PIDTYPE_PID);
	result = pid_nr(kpid);

	printk("the state of the task is:%ld\n",task->state);
	printk("the pid of the task is:%d\n",task->pid);
	printk("the tgid of the task is:%d\n",task->tgid);
	
	printk("the kthread_run result is:%d\n",result);
	printk("out pid_task_init.\n");
	return 0;
}

static void __exit pid_task_exit(void){
	printk("Goodbye pid_task\n");
}

module_init(pid_task_init);
module_exit(pid_task_exit);

MODULE_LICENSE("GPL");
