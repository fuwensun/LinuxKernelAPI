/*
 *
 *
 */

#include <linux/module.h>
#include <linux/sched.h>
#include <linux/pid.h>
#include <linux/wait.h>
#include <linux/kthread.h>
#include <linux/delay.h>

static wait_queue_head_t head;
static wait_queue_entry_t data;

int my_function(void *argc){
	int result = -1;
	int result1 = -1;
	printk("-->in the kernel thread function!\n");
	
	printk("-->the current pid is:%d\n",current->pid);
	printk("-->the state of the parent process before default_wake_function is:%ld\n", current->real_parent->state);
	if(data.private != NULL){
		set_current_state(TASK_UNINTERRUPTIBLE);
		//msleep(5000);	//5s 后唤醒主进程
		result = schedule_timeout(5000);
		result1 = default_wake_function(&data,TASK_ALL,0,NULL);
	}
	printk("-->the state of the parent process after default_wake_fucnton is:%ld\n",current->real_parent->state);

	printk("-->the rssult of the schedule_timeout is:%d\n",result);
	printk("-->the result of the default_wake_functon is:%d\n",result1);
	
	printk("-->out the kernel thread function!\n\n");
}

static int __init default_wake_function_init(void){
	int pidt = 0;
	int result1 = 0;
	int result2 = 0;
	struct task_struct *task = NULL;
	struct pid *kpid = NULL;

	printk("into default_wake_function_init.\nthe current pid is:%d\n",current->pid);

	task = kthread_run(my_function,NULL,"XXX");
	kpid = get_task_pid(task,PIDTYPE_PID);
	pidt = pid_vnr(kpid);

	init_waitqueue_head(&head);
	init_waitqueue_entry(&data,current);
	add_wait_queue(&head,&data);
	
	set_current_state(TASK_UNINTERRUPTIBLE);
//	set_current_state(TASK_INTERRUPTIBLE);
	result1 = schedule_timeout(10000);	//主进程睡眠10s,后醒
//	result1 = schedule_timeout(1000);	//主进程睡眠1s，先醒

	if(data.private != NULL)
		result2 = default_wake_function(&data,TASK_ALL,0,NULL);
	printk("the result of the kthread_run is:%d\n",pidt);
	printk("the rssult of the schedule_timeout is:%d\n",result1);
	printk("the result of the default_wake_function is:%d\n",result2);
	printk("the current pid is:%d\n",current->pid);

	printk("out default_wake_function_init.\n\n");
	return 0;
}

static void __exit default_wake_function_exit(void){
	printk("Goodbye default_wake_function\n\n");

}

module_init(default_wake_function_init);
module_exit(default_wake_function_exit);

MODULE_LICENSE("GPL");

/*sfw**
--------------------------------
$ sudo rmmod default_wake_function.ko | sudo dmesg -c	//sfw**
[  325.664438] into default_wake_function_init.
               the current pid is:1949
[  325.664501] -->in the kernel thread function!
[  325.664502] -->the current pid is:1951
[  325.664503] -->the state of the parent process before default_wake_function is:1
[  346.944336] -->the state of the parent process after default_wake_fucnton is:1
[  346.944339] -->the rssult of the schedule_timeout is:0		<------
[  346.944341] -->the result of the default_wake_functon is:1
[  346.944342] -->out the kernel thread function!

[  346.944420] the result of the kthread_run is:1951
[  346.944422] the rssult of the schedule_timeout is:4677		<------
[  346.944424] the result of the default_wake_function is:0
[  346.944426] the current pid is:1949							<------
[  346.944427] out default_wake_function_init.

--------------------------------
$ ps -aux | grep "default_wake"
root      1947  0.0  0.1  72716  4492 pts/0    S+   17:42   0:00 sudo insmod default_wake_function.ko
root      1949  0.0  0.0   4656   944 pts/0    D+   17:42   0:00 insmod default_wake_function.ko		<------

*/
