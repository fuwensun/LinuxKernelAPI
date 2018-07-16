/*
 * linux/wait.h
 * linux/kernel/sched.c
 * void __wake_up(wait_queue_head_t *q, unsigned int mode, int nr,void *key)
 * __wake_up - wake up threads blocked on a waitqueue.
 * @wq_head: the waitqueue
 * @mode: which threads
 * @nr_exclusive: how many wake-one or wake-many threads to wake up
 * @key: is directly passed to the wakeup function(sfw add  threads func)
 */

#include <linux/module.h>
#include <linux/sched.h>
#include <linux/pid.h>
#include <linux/wait.h>
#include <linux/list.h>
#include <linux/kthread.h>

static wait_queue_head_t head;

int my_function(void *argc){
	printk("in the kernel thread function!");
	printk("the current pid is:%d\n",current->pid);
	printk("the state of the real_parent is:%ld\n",current->real_parent->state);
	__wake_up(&head,TASK_ALL,0,NULL);
	printk("the state of the real_parent after __wake_up is:%ld\n",current->real_parent->state);
	printk("out the kernel thread function\n");
	return 0;
}

static int __init __wake_up_init(void){
	long left_time = 0;
	wait_queue_entry_t data;
	struct task_struct *task = NULL;
	struct pid *kpid = NULL;

	printk("into __wake_up_init.\n");
	task = kthread_run(my_function,NULL,"xxx");

	init_waitqueue_head(&head);
	init_waitqueue_entry(&data,current);
	add_wait_queue(&head,&data);

	left_time = wait_event_timeout(head,NULL,2000);

	printk("the return result of the wait_evet_timeout is:%ld\n",left_time);
	printk("the current pid is:%d\n",current->pid);
	printk("out __wake_up_init.\n");
	return 0;
}

static void __exit __wake_up_exit(void){
	printk("Goodbye __wake_up\n");
}

module_init(__wake_up_init);
module_exit(__wake_up_exit);

MODULE_LICENSE("GPL");

