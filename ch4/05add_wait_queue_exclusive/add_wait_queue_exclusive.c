/*
 * linux/wait.h
 * linux/kernel/wait.c
 * void add_wait_queue_exclusive(wait_queue_head_t *q, wait_queue_t *wait) 
 * 将等待队列元素wait插入等待队列q尾部，并设置wait的flags为WQ_FLAG_EXCLUSIVE,即为1,就是最高优先级
 */

#include <linux/module.h>
#include <linux/sched.h>
#include <linux/list.h>
#include <linux/kthread.h>

int my_function(void *argc){
	printk("in the kernel thread function!\n");
	printk("the current pid is:%d\n",current->pid);
	printk("out the kernel thread function!\n");
	return 0;
}

static int __init add_wait_queue_init(void){
	pid_t pidt = 0;
	pid_t pidt1 = 0;
	int wait_queue_num = 0;
	wait_queue_head_t head;
	wait_queue_entry_t data, data1, *curr, *next;
	struct task_struct *task = NULL, *task1 = NULL;
	struct pid *pid = NULL, *pid1 = NULL;

	printk("into add_wait_queue_init.\n");
	
	task = kthread_run(my_function,NULL,"XXX");
	task1= kthread_run(my_function,NULL,"YYY");

	pid = get_task_pid(task,PIDTYPE_PID);
	pid1= get_task_pid(task1,PIDTYPE_PID);

	pidt  = pid_nr(pid);
	pidt1 = pid_nr(pid1);

	init_waitqueue_head(&head);
	init_waitqueue_entry(&data,task);
	init_waitqueue_entry(&data1,task1);
	add_wait_queue_exclusive(&head,&data);
	add_wait_queue_exclusive(&head,&data1);

	list_for_each_entry_safe(curr, next, &(head.head), entry){		//重要

		wait_queue_num++;
		printk("the flag value of the current data of the waitqueue is:%d\n",curr->flags);
		printk("the pid value of the current data of the waitqueue is:%d\n",((struct task_struct *)(curr->private))->pid);	
	}

	printk("the value of the wait_queue_num is:%d\n",wait_queue_num);
	printk("the pidt of the kthread_run is:%d\n",pidt);
	printk("the pidt1 of the kthread_run is:%d\n",pidt1);
        printk("the current pid is :%d\n",current->pid);
	printk("out add_wait_queue_init.\n");	
	
	return 0;
}

static void __exit add_wait_queue_exit(void){
	printk("Goodbye add_wait_queue\n");
}

module_init(add_wait_queue_init);
module_exit(add_wait_queue_exit);

MODULE_LICENSE("GPL");
