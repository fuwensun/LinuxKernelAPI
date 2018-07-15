/*
 * linux/sched.h
 * linux/kernel/fork.c
 * struct mm_struct *get_task_mm(struct task_struct *task)
 * 根据进程结构体task_struct获取对应的内存信息mm_struct。
 */

#include <linux/module.h>
#include <linux/sched.h>
#include <linux/sched/mm.h>
#include <linux/pid.h>
#include <linux/mm_types.h>
#include <linux/kthread.h>
#include <linux/delay.h>

int my_function(void *argc){
	printk("in the kernel thread function!\n");
	printk("the current PID is: %d\n", current->pid);
	return 0;
}

static int __init get_task_mm_init(void){
	int result = 0;
	struct pid *kpid = NULL;
	struct task_struct *task = NULL;
	struct mm_struct *mm = NULL;
	
	printk("into get_task_mm_init");
	task = kthread_run(my_function,NULL,"xxx");
	
	mm = get_task_mm(task);
	if(NULL != mm){
		kpid = get_task_pid(task,PIDTYPE_PID);
		result = pid_vnr(kpid);

		printk("the mm_users of the mm_struct is:%d\n", mm->mm_users);
		printk("the mm_users of teh mm_struct is:%d\n", mm->mm_count);

		printk("the tgid of the mm_struct is:%d\n", mm->owner->tgid);
		printk("the pid of the mm_struct is:%d\n", mm->owner->pid);

	}else{
		printk("kernel thread mm_struct  is NULL!");
		return -1;
	}
	
	printk("the current PID is:%d\n",current->pid);
	printk("the kthread_run result is:%d\n", result);
	printk("out get_task_mm_init");

	return 0;

}


static void __exit get_task_mm_exit(void){
	printk("Goodbye get_task_mm\n");
}

module_init(get_task_mm_init);
module_exit(get_task_mm_exit);

MODULE_LICENSE("GPL");
