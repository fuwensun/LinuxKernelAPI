/*
 * linux/wait.h
 * linux/kernel/wait.c
 * int autoremvoe_wake_function(wait_queue_t *wait, unsigned mode, int sync, void *key)
 * 从等待队列中唤醒满足条件的进程并删除。
 * sync：1同步，0异步。唤醒方式。
 * key：？？
 */


#include <linux/module.h>
#include <linux/sched.h>
#include <linux/list.h>
#include <linux/wait.h>
#include <linux/kthread.h>

wait_queue_head_t head;
wait_queue_entry_t data;

int my_function(void *argc){
	int wait_queue_num = 0, return_data = 0;
	wait_queue_entry_t *curr,*next;

	printk("in the kernel thread function!\n");
	
	list_for_each_entry_safe(curr, next, &head.head, entry){
		wait_queue_num ++;
		printk("the pid value of the current data of the waitqueue is:%d\n",((struct task_struct *)(curr->private))->pid);
		printk("the state of the current data of the waitqueue is:%ld\n",((struct task_struct *)(curr->private))->state);
		
	}
	
	printk("the value of the wait_queue_num is:%d\n",wait_queue_num);
	
	return_data = autoremove_wake_function(&data,TASK_NORMAL,1,NULL);
	
	list_for_each_entry_safe(curr, next, &head.head, entry){
		wait_queue_num ++;
		printk("the pid value of the current data of the waitqueue is:%d\n",((struct task_struct *)(curr->private))->pid);
		printk("the state of the current data of the waitqueue is:%ld\n",((struct task_struct *)(curr->private))->state);
		
	}
	
	printk("the value of the wait_queue_num is:%d\n",wait_queue_num);
	printk("the return_data of the autoremove_wake_function is:%d\n", return_data);
	printk("the current pid is:%d\n",current->pid);
	printk("out the kernel thread function\n");
	return 0;

}

static int __init autoremove_wake_function_init(void){
	pid_t pidt = 0,pidt1 = -2, wait_queue_num = 0, left_time;
	wait_queue_entry_t *curr, *next;
	struct task_struct *task = NULL;

	task = kthread_run(my_function,NULL,"xxx");

	init_waitqueue_head(&head);
	init_waitqueue_entry(&data,current);
	add_wait_queue(&head,&data);

	// prepare_to_wait(q, &wait, TASK_INTERRUPTIBLE);prepare_to_wait(q, &wait, TASK_INTERRUPTIBLE);
	// schedule_timeout - sleep until timeout
	// sleep_on_timeout is deprecated
	prepare_to_wait(&head,&data,TASK_UNINTERRUPTIBLE);
	left_time =  schedule_timeout(100);
	
	if(data.private != NULL)
		pidt1 = autoremove_wake_function(&data,TASK_ALL,0,NULL);

	list_for_each_entry_safe(curr,next, &head.head, entry){
		wait_queue_num++;
		printk("the pid value of the current data of the waitqueue is:%d\n",((struct task_struct *)(curr->private))->pid);
		printk("the state of the current data of the waitqueue is:%ld\n",((struct task_struct *)(curr->private))->state);
	}

	printk("the left_time of the schedule_timeout is:%d\n",left_time);
	printk("the return pidt1 of the autoremove_wake_function is:%d\n",pidt1);
	printk("the value of the wait_queue_num is:%d\n",wait_queue_num);

	printk("the pidt of the kthread_run is:%d\n",task->pid);
	printk("the current pid is:%d\n",current->pid);
	printk("out autoremove_wake_function_init.\n");


	return 0;	
}

static void __exit autoremove_wake_function_exit(void){
	printk("Goodbye autoremove_wake_function\n");
}

module_init(autoremove_wake_function_init);
module_exit(autoremove_wake_function_exit);

MODULE_LICENSE("GPL");
