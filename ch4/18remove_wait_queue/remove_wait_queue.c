/*
linux/wait.h
kernel/sched/wait.c
void remove_wait_queue(struct wait_queue_head *wq_head, struct wait_queue_entry *wq_entry)
把等待量iwq_entry从等待队列wq_head中移除.
*/

#include <linux/module.h>
#include <linux/sched.h>
#include <linux/list.h>
#include <linux/kthread.h>
#include <linux/wait.h>
#include <linux/pid.h>

int my_function(void *argc){
	printk("--->in the kernel thread function!\n");
	printk("--->the current pid is: %d\n",current->pid);
	printk("--->out the kernel thread function!\n");
	return 0;
}

static int __init remove_wait_queue_init(void){
	pid_t pidt=0,pidt1=0,pidt2=0;
	struct task_struct *task = NULL, *task1 = NULL, *task2 = NULL;
	struct pid *kpid = NULL, *kpid1 = NULL, *kpid2 = NULL;
	wait_queue_head_t head;
	wait_queue_entry_t data,data1,data2,*curr,*next;
	int wait_queue_num = 0;

	printk("into remove_wait_queue_init.\n");

	task = kthread_run(my_function,NULL,"AAA");
	task1 = kthread_run(my_function,NULL,"BBB");
	task2 = kthread_run(my_function,NULL,"CCC");

	kpid = get_task_pid(task,PIDTYPE_PID);
	kpid1 = get_task_pid(task1,PIDTYPE_PID);
	kpid2 = get_task_pid(task2,PIDTYPE_PID);

	pidt = pid_vnr(kpid);
	pidt1 = pid_vnr(kpid1);
	pidt2 = pid_vnr(kpid2);
	
	init_waitqueue_head(&head);

	init_waitqueue_entry(&data,task);
	init_waitqueue_entry(&data1,task1);
	init_waitqueue_entry(&data2,task2);

	add_wait_queue(&head,&data);
	add_wait_queue_exclusive(&head,&data1);
	add_wait_queue(&head,&data2);

	list_for_each_entry_safe(curr, next, &head.head, entry){
		wait_queue_num++;
		printk("the flag value of the current data of the waitqueue is: %d\n",curr->flags);
		printk("the pid value of the current data of the waitqueue is : %d\n",((struct task_struct *)(curr->private))->pid);
	}
	printk("the value of the wait_queue_num is: %d\n",wait_queue_num);

	wait_queue_num = 0;
	remove_wait_queue(&head,&data2);

	list_for_each_entry_safe(curr, next, &head.head, entry){
		wait_queue_num++;
		printk("the flag value of the current data of the waitqueue is: %d\n",curr->flags);
		printk("the pid value of the current data of the waitqueue is : %d\n",((struct task_struct *)(curr->private))->pid);
		
	}
	printk("the value of the wait_queue_num is: %d\n",wait_queue_num);

	printk("the pidt of the kthread_run is: %d\n",pidt);
	printk("the pidt1 of the kthread_run is: %d\n",pidt1);
	printk("the pidt2 of the kthread_run is: %d\n",pidt2);
	printk("the current pid is: %d\n",current->pid);

	printk("out remove_wait_queue_init.\n");
	return 0;
}

static void __exit remove_wait_queue_exit(void){
	printk("Goodbye remove_wait_queue");
}

module_init(remove_wait_queue_init);
module_exit(remove_wait_queue_exit);

MODULE_LICENSE("GPL");
