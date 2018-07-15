/*
 * linux/sched.h
 * linux/kernel/fork.c
 * void mmput(struct mm_struct *)
 * 减一使用计数，为0时释放。
 */

#include <linux/module.h>
#include <linux/pid.h>
#include <linux/sched.h>
#include <linux/sched/mm.h>
#include <linux/kthread.h>
#include <linux/mm.h>

int my_function(void *argc){
	printk("in the kernel thread function!\n");
	return 0;
}

static int __init mmput_init(void){
	int result = 0;
       	int result1 = 0;
	struct task_struct *task = NULL;
	struct pid *kpid = NULL;
	struct mm_struct *mm = NULL;

	printk("into mmput_init.\n");
	task = kthread_run(my_function,NULL,"xxx");
	kpid = get_task_pid(task,PIDTYPE_PID);
	result = pid_vnr(kpid);
	mm = get_task_mm(task);

	if(mm != NULL){
		printk("the mm_users of the mm_struct is:%d\n", mm->mm_users);
		printk("the mm_count of teh mm_struct id:%d\n", mm->mm_count);
		printk("the tgid of the mm_struct is:%d\n",mm->owner->tgid);
		printk("the pid of the mm_struct is:%d\n",mm->owner->pid);

		mmput(mm);
		printk("the new value of the mm_sturct after the function mmput:\n");
		printk("the mm_users of the mm_struct is:%d\n", mm->mm_users);
		printk("the mm_count of teh mm_struct id:%d\n", mm->mm_count);
		printk("the tgid of the mm_struct is:%d\n",mm->owner->tgid);
		printk("the pid of the mm_struct is:%d\n",mm->owner->pid);
	}else{
		printk("the mm is NULL");
	}


	printk("the kthread_run result is:%d\n",result);
	printk("out mmput_init.\n");

	return 0;	
}


static void __exit mmput_exit(void){
	printk("Goodbye mmput\n");
}

module_init(mmput_init);
module_exit(mmput_exit);

MODULE_LICENSE("GPL");
