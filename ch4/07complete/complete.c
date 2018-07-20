/*
 * linux/completion.h>
 * linux/kernel/sched.c
 * void complete(struct completion *)
 * 逐个唤醒睡眠在这个完成量上的进程。
 */

#include <linux/module.h>
#include <linux/sched.h>
#include <linux/pid.h>
#include <linux/wait.h>
#include <linux/completion.h>
#include <linux/kthread.h>

static struct completion comple;

int my_function(void *argc){
	printk("in the kernel thread function!");
	printk("the current pid is:%d\n",current->pid);
	
	printk("the state of the real_parent is:%ld\n",current->real_parent->state);
	printk("the value of done of the comple:%d\n",comple.done);

	complete(&comple);
	printk("the value of done of the comple:%d\n",comple.done);

	printk("the state of the real_parent is:%ld\n",current->real_parent->state);
	printk("out the kerenl thread function\n");
	return 0;
}

static int __init complete_init(void){
	int pidt = 0;
	long left_time = 0;
	wait_queue_entry_t data;
	struct task_struct *task = NULL;

	printk("into complete_init.\n");
	
	task = kthread_run(my_function,NULL,"xxx");

	init_completion(&comple);
	init_waitqueue_entry(&data,current);
	add_wait_queue(&(comple.wait),&data);

	prepare_to_wait(&(comple.wait),&data,TASK_UNINTERRUPTIBLE);
	left_time = schedule_timeout(100);

	printk("the return result of the kthread is:%d\n",task->pid);

	printk("the return result of the shcedule_timeout is:%d\n",left_time);
       	printk("the current pid is:%d\n",current->pid);
	
	printk("out complete_init.\n");
	return 0;
}

static void __exit complete_exit(void){
	printk("Goodbye complete\n");
}

module_init(complete_init);
module_exit(complete_exit);

MODULE_LICENSE("GPL");
