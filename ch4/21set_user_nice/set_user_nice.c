/*
linux/sched.h
kernel/sched/core.c
void set_user_nice(struct task_struct *p, long nice)
设置进程p的nice值
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

static int __init set_user_nice_init(void){
	
	pid_t pidt;
	struct task_struct *task = NULL;
	struct pid *kpid = NULL;

	printk("into set_user_nice_init.\n");
	
	task = kthread_run(my_function,NULL,"XXX");
	kpid = get_task_pid(task,PIDTYPE_PID);
	pidt = pid_vnr(kpid);

	printk("the static_prio of the child thread is: %d\n",task->static_prio);
	printk("the nice of the child thread is: %d\n",task_nice(task));
	printk("the prio of the child thread is: %d\n",task->prio);

	set_user_nice(task,-20);

	printk("the new value static_prio of the child thread is: %d\n",task->static_prio);
	printk("the new value nice of the child thread is: %d\n",task_nice(task));
	printk("the new value prio of the child thread is: %d\n",task->prio);
	printk("the pidt of the kthread_run is: %d\n",pidt);
	printk("the current pid is: %d\n",current->pid);
	
	printk("out set_user_nice_init.\n");
	return 0;
}

static void __exit set_user_nice_exit(void){
	printk("Goodbye set_user_nice\n");
}

module_init(set_user_nice_init);
module_exit(set_user_nice_exit);

MODULE_LICENSE("GPL");
