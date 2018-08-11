/*
 * linux/completion.h
 * linux/sched/completion.c
 * boll completion_done(struct completion *x)
 * 查看完成量上是否完成，有等待者返回0，无返回1. 
 */

/**
 *	completion_done - Test to see if a completion has any waiters
 *	@x:	completion structure
 *
 *	Return: 0 if there are waiters (wait_for_completion() in progress)
 *		 1 if there are no waiters.
 *
 *	Note, this will always return true if complete_all() was called on @X.
 */
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/pid.h>
#include <linux/completion.h>
#include <linux/wait.h>
#include <linux/list.h>
#include <linux/kthread.h>

static struct completion comple;

int my_function(void *argc){

	bool result = -1;
	wait_queue_head_t head;
	wait_queue_entry_t data;
	
	printk("in the kernel thread function!\n");
	
	init_waitqueue_head(&head);
	init_waitqueue_entry(&data,current);
	add_wait_queue(&head,&data);

	prepare_to_wait(&head,&data,TASK_UNINTERRUPTIBLE);
	schedule_timeout(100);

	//----
	complete(&comple);
	printk("the value of done of the comple is: %d\n",comple.done);

	result = completion_done(&comple);
	printk("the return result of the completion_done is: %d\n",result);

	printk("the current pid is: %d\n",current->pid);
	printk("the state of the parent is: %ld\n",current->real_parent->state);
	
	printk("out the kernel thread function");
}	

static int __init completion_done_init(void){
	pid_t pidt = 0;
	struct pid *kpid = NULL;
	struct task_struct *task = NULL;

	wait_queue_entry_t data;
	
	printk("into completion_done_init.\n");

	task = kthread_run(my_function,NULL,"xxx");
	kpid = get_task_pid(task,PIDTYPE_PID);
	pidt = pid_vnr(kpid);

	init_completion(&comple);
	init_waitqueue_entry(&data,task);
	__add_wait_queue(&(comple.wait), &data);
	wait_for_completion(&comple);

	printk("the pidt of the kthread_run is: %d\n", pidt);
	printk("the current pid is: %d\n",current->pid);
	printk("out completion_dome_init.\n");
	return 0;

}

static void __exit completion_done_exit(void){
	printk("Goodbye completion_done\n");
}

module_init(completion_done_init);
module_exit(completion_done_exit);

MODULE_LICENSE("GPL");
