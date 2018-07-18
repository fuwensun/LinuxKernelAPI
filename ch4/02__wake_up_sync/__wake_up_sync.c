/*
 * linux/wait.h
 * linux/kernel/sched.c
 * void __wake_up_sync(wait_queue_head_t *q, unsigned int mode, int nr)
 * 唤醒等待队列中处于mode状态的进程
 * @wq_head: the waitqueue
 * @mode: which threads
 * @nr_exclusive: how many wake-one or wake-many threads to wake up
 */

#include <linux/module.h>
#include <linux/sched.h>
#include <linux/pid.h>
#include <linux/wait.h>
#include <linux/list.h>
#include <linux/kthread.h>

static wait_queue_head_t head;

int my_function(void *argc){
	printk("in the kernel thread function!\n");
	printk("the current pid is:%d\n",current->pid);
	printk("the state of the real_parent is:%ld\n",current->real_parent->state);
	__wake_up_sync(&head,TASK_ALL,0);
	printk("the state of the real_parent after __wake_up_sync is:%ld\n",current->real_parent->state); 
	printk("out the kernel thread function\n");
	return 0;
}

static int __init __wake_up_sync_init(void){
	long left_time = 0;
	struct task_struct *task = NULL;
	struct pid *kpid = NULL;
	wait_queue_entry_t data;

	printk("into __wake_up_sync_init.\n");
	task = kthread_run(my_function,NULL,"XXX");

	init_waitqueue_head(&head);
	init_waitqueue_entry(&data,current);
	add_wait_queue(&head,&data);

	left_time = wait_event_timeout(head,NULL,2000);

	printk("the return of the wait_event_timeout is:%ld\n",left_time);
	printk("the pid_t of the kthread_run is:%d\n",task->pid);
	printk("out __wake_up_sync_init.\n");
	return 0;

}

static void __exit __wake_up_sync_exit(void){
	printk("Goodbye __wake_up_sync\n");
}

module_init(__wake_up_sync_init);
module_exit(__wake_up_sync_exit);

MODULE_LICENSE("GPL");
