/*
linux/sched.h
kernel/sched/core.c
int wake_up_process(struct task_struct *p)
唤醒进程。返回1，唤醒成功；返回0，进程已经是RUNNING。
*/

#include <linux/module.h>
#include <linux/sched.h>
#include <linux/pid.h>
#include <linux/wait.h>
#include <linux/kthread.h>

int my_function(void *argc){
	int data = -1;
	printk("--->in the kernel thread function!\n");
	printk("--->the current pid is: %d\n",current->pid);
	printk("--->the state of the parent process before wake_up_process is: %ld\n",current->real_parent->state);
	data = wake_up_process(current->real_parent);
	printk("--->the state of the parent process after wake_up_process is: %ld\n",current->real_parent->state);
	printk("--->the result of the wake_up_process is: %d\n",data);
	printk("--->out the kernel thread function!\n");
	return 0;
}

static int __init wake_up_process_init(void){
	
	pid_t pidt = 0;
	int result = 0,result1 = 1;
	struct task_struct *task = NULL;
	struct pid *kpid = NULL;
	wait_queue_head_t head;
	wait_queue_entry_t data;

	printk("into wake_up_process_init.\n");

	task = kthread_run(my_function,NULL,"XXX");
	kpid = get_task_pid(task,PIDTYPE_PID);
	pidt = pid_vnr(kpid);

	init_waitqueue_head(&head);
	init_waitqueue_entry(&data,current);

	prepare_to_wait(&head,&data,TASK_INTERRUPTIBLE);
	result = schedule_timeout(10);

	result1 = wake_up_process(current);
	
	printk("the result of the kthread_run is: %d\n",pidt);
	printk("the reuslt of the schedule_timeout is: %d\n",result);
	printk("the result of the wake_up_process is: %d\n",result1);
	printk("the current pid is: %d\n",current->pid);

	printk("out wake_up_process_exit.\n");
	return 0;	
}

static void __exit wake_up_process_exit(void){
	printk("Goodbye wake_up_process\n");
}

module_init(wake_up_process_init);
module_exit(wake_up_process_exit);

MODULE_LICENSE("GPL");
