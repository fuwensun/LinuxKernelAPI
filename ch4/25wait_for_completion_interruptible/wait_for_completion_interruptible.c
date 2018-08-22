/*
linux/completion.h
kernel/sched/completion.c
int __sched wait_for_completion_interruptible(struct completion *x)
可中断的阻塞等待完成量。如果x.done大于0，返回0；被中断，返回-ERESTARTSYS。
*/

/**
 * wait_for_completion_interruptible: - waits for completion of a task (w/intr)
 * @x:  holds the state of this particular completion
 *
 * This waits for completion of a specific task to be signaled. It is
 * interruptible.
 *
 * Return: -ERESTARTSYS if interrupted, 0 if completed.
 */

#include <linux/module.h>
#include <linux/sched.h>
#include <linux/pid.h>
#include <linux/list.h>
#include <linux/wait.h>
#include <linux/completion.h>
#include <linux/kthread.h>
#include <linux/delay.h>

static struct completion comple;

int my_function(void *argc){
	
	wait_queue_head_t head;
	wait_queue_entry_t data;

	printk("--->in the kernel thread function!\n");

	init_waitqueue_head(&head);
	init_waitqueue_entry(&data,current);
	prepare_to_wait(&head,&data,TASK_INTERRUPTIBLE);
	schedule_timeout(10);
	
	printk("--->the current pis is: %d\n",current->pid);

	printk("--->the state of the parent is: %ld\n",current->real_parent->state);

	//屏蔽这句，可以用 ctrl+c 中断 xxx_init 中 
	//wait_for_completion_interruptible的阻塞 
	//complete(&comple);
	printk("--->complete(&comple) run !!!                 +1 <----");
	printk("the value of done of the comple is: %d\n",comple.done);

	printk("--->out the kernel thread function!\n");
	return 0;
}

static int __init wait_for_completion_interruptible_init(void){
	pid_t pidt = 0;
	struct task_struct *task = NULL;
	struct pid *kpid = NULL;

	wait_queue_entry_t data;
	int result = 0;
	printk("into wait_for_completion_interrutible_init.\n");

	task = kthread_run(my_function,NULL,"XXX");
	kpid = get_task_pid(task,PIDTYPE_PID);
	pidt = pid_vnr(kpid);

	init_completion(&comple);
	init_waitqueue_entry(&data,task);
	add_wait_queue_exclusive(&comple.wait,&data);

	printk("the value of done of the comple is: %d\n",comple.done);
	//-------------------	
	result = wait_for_completion_interruptible(&comple);
	printk("wait_for_completion(&comple) run !!!          -1 <----");
	printk("the value of done of the comple is: %d\n",comple.done);
	printk("the result of the wait_for_completion_interruptible is: %d\n",result);
	
	printk("the pidt of the kthread_run is: %d\n",pidt);
	printk("the current pid is: %d\n",current->pid);

	printk("out wait_for_completion_interruptible_init,\n");

	return 0;
}

static void __exit wait_for_completion_interruptible_exit(void){
	printk("Goodbye wait_for_interruptible_completion.\n");
}


module_init(wait_for_completion_interruptible_init);
module_exit(wait_for_completion_interruptible_exit);

MODULE_LICENSE("GPL");
