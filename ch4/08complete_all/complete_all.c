/*
 * linux/completion.h
 * linux/sched/completion.c
 * void complete_all(struct completion *x)
 * 通知所有睡眠在这completion上的进程。
 */
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/pid.h>
#include <linux/wait.h>
#include <linux/completion.h>
#include <linux/kthread.h>

static struct completion comple;

int my_function(void *argc){
	printk("in the kernel thread function!\n");
	printk("the current pid is:%d\n",current->pid);
	printk("the state of the real_parent is:%ld\n",current->real_parent->state);
	printk("the value of the done of the comple is:%d\n",comple.done);

	complete_all(&comple);
	printk("the state of the real_parent is:%ld\n",current->real_parent->state);
	printk("the value of the done of the comple is:%d\n",comple.done);

	printk("out the kernel thread function\n");
	return 0;
}

static int __init complete_all_init(void){
	pid_t pidt = 0;
	long left_time = 0;
	struct task_struct *task = NULL;
	struct pid *kpid = NULL;
	wait_queue_entry_t data;

	printk("into complete_all_init.\n");

//	task = kthread_run(my_function,NULL,"XXX");
//	kpid = get_task_pid(task,PIDTYPE_PID);
//	pidt = pid_nr(kpid);

	init_completion(&comple);
	init_waitqueue_entry(&data,current);
	add_wait_queue(&comple.wait,&data);

	prepare_to_wait(&comple.wait,&data,TASK_UNINTERRUPTIBLE);
//	prepare_to_wait(&comple.wait,&data,TASK_INTERRUPTIBLE);
	left_time = schedule_timeout(100);

	remove_wait_queue(&comple.wait,&data);	//*******sfw_add********

	task = kthread_run(my_function,NULL,"XXX");
	kpid = get_task_pid(task,PIDTYPE_PID);
	pidt = pid_nr(kpid);


	printk("the return result of the schedule_timeout is:%ld\n",left_time);
	printk("the return result of the kthread_run is:%d\n",pidt);
	printk("the current pid is:%d\n",current->pid);
	printk("out complete_all_init.\n");
	return 0;

}

static void __exit complete_all_exit(void){
	printk("Goodbye complete_all\n");
}

module_init(complete_all_init);
module_exit(complete_all_exit);

MODULE_LICENSE("GPL");
