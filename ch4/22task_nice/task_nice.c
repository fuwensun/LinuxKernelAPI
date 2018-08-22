/*
linux/sched.h
static inline int task_nice(const struct task_struct *p)
获取进程的nice值。
*/

/**
 * task_nice - return the nice value of a given task.
 * @p: the task in question.
 *
 * Return: The nice value [ -20 ... 0 ... 19 ].
 */

#include <linux/module.h>
#include <linux/sched.h>
#include <linux/pid.h>
#include <linux/kthread.h>

int my_function(void *argc){
	printk("--->in the kernel thread function!\n");
	printk("--->the current static_prio is: %d\n",current->static_prio);
	printk("--->the current nice is: %d\n",task_nice(current));
	printk("--->the current pid is: %d\n",current->pid);
	printk("--->out the kernel thread function!\n");
	return 0;
}

static int __init task_nice_init(void){
	pid_t pidt;
	int priority = 0;
	struct task_struct *task = NULL;
	struct pid *kpid = NULL;

	printk("into task_nice_init.\n");

	task = kthread_run(my_function,NULL,"XXX");
	kpid = get_task_pid(task,PIDTYPE_PID);
	pidt = pid_vnr(kpid);

	priority = task_nice(task);

	printk("the static_prio of the child thread is: %d\n",task->static_prio);
	printk("the nice of the child thread is: %d\n",priority);
	printk("the pidt of the kthread_run is: %d\n",pidt);
	printk("the current pid is: %d\n",current->pid);
	printk("the current nice is: %d\n",task_nice(current));

	printk("out task_nice_init.\n");
	return 0;
}

static void __exit task_nice_exit(void){
	printk("Goodbye task_nice.\n");
}

module_init(task_nice_init);
module_exit(task_nice_exit);

MODULE_LICENSE("GPL");
