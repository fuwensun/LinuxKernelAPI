/*
linux/wait.h
kernel/sched/wait.c
void prepare_to_wait_exclusive(struct wait_queue_head *wq_head, struct wait_queue_entry *wq_entry, int state)
把等待量wq_entry加入等待队列wq_head尾部并设置当前线程状态为state.
*/

#include <linux/module.h>
#include <linux/sched.h>
#include <linux/list.h>
#include <linux/kthread.h>
#include <linux/pid.h>
#include <linux/wait.h>
#include <linux/delay.h>

int my_function(void *argc){
	msleep(1000);
	printk("--->in the kernel thread function!\n");
	printk("--->the current pid is: %d\n",current->pid);
	printk("--->out the kernel thread function.\n");
	return 0;
}

static int __init prepare_to_wait_exclusive_init(void){
	
	pid_t pidt, pidt1, pidt2, pidt3;
	struct task_struct *task = NULL, *task1 = NULL, *task2 = NULL, *task3 = NULL;
	struct pid *kpid = NULL, *kpid1 = NULL, *kpid2 = NULL, *kpid3 = NULL;
	
	int wait_queue_num = 0;
	wait_queue_head_t head;
	wait_queue_entry_t data,data1,data2,data3,*curr,*next;

	printk("into prepare_to_wait_exclusive_init.\n");

	task  = kthread_run(my_function,NULL,"AAA");
	task1 = kthread_run(my_function,NULL,"BBB");
	task2 = kthread_run(my_function,NULL,"CCC");
	task3 = kthread_run(my_function,NULL,"DDD");

	kpid  = get_task_pid(task,PIDTYPE_PID);
	kpid1 = get_task_pid(task1,PIDTYPE_PID);
	kpid2 = get_task_pid(task2,PIDTYPE_PID);
	kpid3 = get_task_pid(task3,PIDTYPE_PID);

	pidt  = pid_vnr(kpid);
	pidt1 = pid_vnr(kpid1);
	pidt2 = pid_vnr(kpid2);
	pidt3 = pid_vnr(kpid3);
	
	init_waitqueue_head(&head);
	
	printk("the state of the current thread is: %ld\n",current->state);
	
	INIT_LIST_HEAD(&data.entry);		//sfw** 初始化为empty后才能成功加入队列,下一句 
	init_waitqueue_entry(&data,task);
	prepare_to_wait(&head,&data,130);
	printk("the state of the current thread is: %ld\n",current->state);
	
	INIT_LIST_HEAD(&data1.entry);
	init_waitqueue_entry(&data1,task1);
	prepare_to_wait_exclusive(&head,&data1,2);
	printk("the state of the current thread is: %ld\n",current->state);
	
	//INIT_LIST_HEAD(&data2.entry);
	init_waitqueue_entry(&data2,task2);
	prepare_to_wait(&head,&data2,1);
	printk("the state of the current thread is: %ld\n",current->state);

	//INIT_LIST_HEAD(&data3.entry);
	init_waitqueue_entry(&data3,task3);
	prepare_to_wait_exclusive(&head,&data3,0);
	printk("the state of the current thread is: %ld\n",current->state);
	
	list_for_each_entry_safe(curr, next, &head.head, entry){
		wait_queue_num ++;
		printk("the flag value of the current data of the waitqueue is: %d\n",curr->flags);
		printk("the pid value of the current data of the waitqueue is: %d\n",((struct task_struct *)(curr->private))->pid);
	}
	printk("the value of the wait_queue_num is: %d\n",wait_queue_num);

	//----------------------------
	INIT_LIST_HEAD(&data2.entry);
	prepare_to_wait(&head,&data2,1);

	INIT_LIST_HEAD(&data3.entry);
	prepare_to_wait_exclusive(&head,&data3,0);
	
	list_for_each_entry_safe(curr, next, &head.head, entry){
		wait_queue_num ++;
		printk("the flag value of the current data of the waitqueue is: %d\n",curr->flags);
		printk("the pid value of the current data of the waitqueue is: %d\n",((struct task_struct *)(curr->private))->pid);
	}
	printk("the value of the wait_queue_num is: %d\n",wait_queue_num);

	//---------------------------
	printk("the pidt  of the kthread_run is: %d\n",pidt);
	printk("the pidt1 of the kthread_run is: %d\n",pidt1);
	printk("the pidt2 of the kthread_run is: %d\n",pidt2);
	printk("the pidt3 of the kthread_run is: %d\n",pidt3);

	printk("the current pid is: %d\n",current->pid);

	printk("out prepare_to_wait_exclusive_init.\n");
	return 0;
}

static void __exit prepare_to_wait_exclusive_exit(void){
	printk("Goodbye prepare_to_wait_exclusive.\n");
}

module_init(prepare_to_wait_exclusive_init);
module_exit(prepare_to_wait_exclusive_exit);

MODULE_LICENSE("GPL");
