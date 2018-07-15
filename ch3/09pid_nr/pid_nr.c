/*
 * linux/pid.h
 * static inline pid_t pid_nr(struct pid *pid)
 * 获取进程描述符对应的全局进程号
 */

#include <linux/module.h>
#include <linux/sched.h>
#include <linux/pid.h>
#include <linux/kthread.h>

int my_function(void *argc){
	printk("in the kernel thread function\n");
	printk("the current pid is:%d\n",current->pid);
	printk("the current tgid is:%d\n",current->tgid);
	printk("out the kernel thread function\n");
	return 0;
}

static int __init pid_nr_init(void){
	int result = 0;
	pid_t nr = 0;
	struct task_struct *task = NULL;
	struct pid *kpid = NULL;

	printk("into pid_nr_init.\n");
	task = kthread_run(my_function,NULL,"xxx");
	kpid = get_task_pid(task,PIDTYPE_PID);
	printk("the level of the pid is:%d\n",kpid->level);
	printk("the pid of the pid is:%d\n",kpid->numbers[kpid->level].nr);

	result = pid_nr(kpid);
	printk("the pid_nr result is:%d\n",nr);
	printk("the current pid is:%d\n",current->pid);
	printk("the current tgid is:%d\n",current->tgid);
	printk("out pid_nr_init.\n");
	return 0;
}

static void __exit pid_nr_exit(void){
	printk("Goodbye pid_nr\n");
}

module_init(pid_nr_init);
module_exit(pid_nr_exit);

MODULE_LICENSE("GPL");

