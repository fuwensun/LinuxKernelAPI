/*


*/

#include <linux/module.h>
#include <linux/sched.h>
#include <linux/list.h>
#include <linux/kthread.h>
#include <linux/pid.h>

int my_function(void *argc){
	printk("--->in the kernel thread function!\n");
	printk("--->the current pid is: %d\n",current->pid);
	printk("--->out the kernel thread function.\n");
	return 0;
}

static int __init finish_wait_init(void){
	pid_t pidt = 0;
	pid_t pidt1 = 0;
	struct task_struct *task  = NULL;
	struct task_struct *task1 = NULL;
	struct pid *kpid = NULL;
	struct pid *kpid1 = NULL;

	int wait_queue_num = 0;
	wait_queue_head_t head;
	wait_queue_entry_t data,data1,*curr,*next;

	printk("into finish_wait_init.");
	
	task = kthread_run(my_function,NULL,"XXX");
	task1 = kthread_run(my_function,NULL,"YYY");

	kpid = get_task_pid(task,PIDTYPE_PID);
	kpid1 = get_task_pid(task1,PIDTYPE_PID);
	
	pidt = pid_vnr(kpid);
	pidt1 = pid_vnr(kpid1);
	
	init_waitqueue_head(&head);

	init_waitqueue_entry(&data,task);
	data.entry.next = &data.entry;
	printk("the state of the current thread is: %ld\n",current->state);
	prepare_to_wait(&head,&data,130);
	printk("the state of the current thread is: %ld\n",current->state);

	init_waitqueue_entry(&data1,task1);
	printk("the state of the current thread is: %ld\n",current->state);
	prepare_to_wait_exclusive(&head,&data1,2);
	printk("the state of the current thread is: %ld\n",current->state);

	list_for_each_entry_safe(curr, next, &head.head, entry){
		wait_queue_num++;
		printk("the flag value of the current data of the waitqueue is: %d\n",curr->flags);
		printk("the value of the current data of the waitqueue is: %d\n",((struct task_struct *)(curr->private))->pid);
	}

	printk("the value of the wait_queue_num is: %d\n",wait_queue_num);
	
	finish_wait(&head,&data);
	printk("the state of the current thread is: %ld\n",current->state);

	list_for_each_entry_safe(curr, next, &head.head, entry){
		wait_queue_num++;
		printk("the flag value of the current data of the waitqueue is: %d\n",curr->flags);
		printk("the value of the current data of the waitqueue is: %d\n",((struct task_struct *)(curr->private))->pid);
	}

	printk("the value of the wait_queue_num is: %d\n",wait_queue_num);
	printk("the pidt of the kthread_run is: %d\n",pidt);
	printk("the pidt1 of the kthread run is: %d\n",pidt1);
	printk("the current pid is: %d\n",current->pid);
	printk("out finish_wait_init.");
	return 0;
}

static void __exit finish_wait_exit(void){
	printk("Goodbye finish_wait.\n");
}

module_init(finish_wait_init);
module_exit(finish_wait_exit);

MODULE_LICENSE("GPL");


