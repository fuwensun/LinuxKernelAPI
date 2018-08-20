/*
 */

#include <linux/module.h>
#include <linux/sched.h>
#include <linux/list.h>
#include <linux/kthread.h>
#include <linux/pid.h>
#include <linux/delay.h>

int my_function(void *argc){
	//msleep(100);
	printk("--->in the kernel thread function!\n");
	printk("--->the current pid is: %d\n",current->pid);
	printk("--->out the kernel thread function");
	return 0;
}

static int __init prepare_to_wait_init(void){
	pid_t pidt = 0;
	pid_t pidt1 = 0;
	struct task_struct *task = NULL;
	struct task_struct *task1 = NULL;
	struct pid *kpid = NULL;
	struct pid *kpid1 = NULL;

	wait_queue_head_t head;
	wait_queue_entry_t data, data1, *curr,*next;
	int wait_queue_num = 0;

	printk("into prepate_to_wait_init.\n");

	task = kthread_run(my_function,NULL,"XXX");
	task1 = kthread_run(my_function,NULL,"YYY");

	kpid = get_task_pid(task,PIDTYPE_PID);
	kpid1 = get_task_pid(task1,PIDTYPE_PID);

	pidt = pid_vnr(kpid);
	pidt1 = pid_vnr(kpid1);
	
	init_waitqueue_head(&head);

	printk("the state of the current thread is: %ld\n",current->state);
	
	//data.entry.next = &data.entry;			//手工初始化链表节点，不推荐！
	INIT_LIST_HEAD(&data.entry);				//sfw**用内核API初始化链表节点，推荐！
	init_waitqueue_entry(&data,task);

	if(data.entry.next != &data.entry){
		printk("data.entry.next != &data.entry");	
	}else{
		printk("data.entry.next == &data.entry");	
	}

	prepare_to_wait(&head,&data,130);
	if(data.entry.next != &data.entry){
		printk("data.entry.next != &data.entry");	
	}else{
		printk("data.entry.next == &data.entry");	
	}
	printk("the state of the current thread is: %ld\n",current->state);

	INIT_LIST_HEAD(&data1.entry);				//sfw**用内核API初始化链表节点，推荐！
	init_waitqueue_entry(&data1,task1);
	
	prepare_to_wait(&head,&data1,1);

	printk("the state of the current thread is: %ld\n",current->state);
	
	list_for_each_entry_safe(curr,next, &head.head,entry){
		wait_queue_num++;
		printk("the flag value of the current data of the waitqueue is: %d\n",curr->flags);
		printk("the pid value of the current data of the waitqueue is: %d\n",((struct task_struct *)(curr->private))->pid);		
	}
	printk("the value of the wait_queue_num is: %d\n",wait_queue_num);

	prepare_to_wait(&head,&data1,1);

	wait_queue_num = 0;	
	list_for_each_entry_safe(curr,next, &(head.head),entry){
		wait_queue_num++;
		printk("the flag value of the current data of the waitqueue is: %d\n",curr->flags);
		printk("the pid value of the current data of the waitqueue is: %d\n",((struct task_struct *)(curr->private))->pid);		
	}
	printk("the value of the wait_queue_num is: %d\n",wait_queue_num);

	printk("the pidt of the kthread_run is: %d\n",pidt);
	printk("the pidt1 of the kthread_run is: %d\n",pidt1);
	printk("the current pid is: %d\n",current->pid);

	printk("out prepare_to_wait_init.\n");

	return 0;
}

static void __exit prepare_to_wait_exit(void){
	printk("Goodbye prepare_to_wait\n");
}

module_init(prepare_to_wait_init);
module_exit(prepare_to_wait_exit);

MODULE_LICENSE("GPL");
