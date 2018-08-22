/*
linux/completion.h
kernel/sched/completion.c
bool wait_for_completion(struct completion *x)
阻塞等待完成量X的
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
	complete(&comple);
	printk("--->complete(&comple) run !!!                 +1 <----");
	printk("the value of done of the comple is: %d\n",comple.done);

	printk("--->out the kernel thread function!\n");
	return 0;
}

static int __init try_wait_for_completion_init(void){
	pid_t pidt = 0;
	struct task_struct *task = NULL;
	struct pid *kpid = NULL;

	wait_queue_entry_t data;

	printk("into try_wait_for_completion_init.\n");

	task = kthread_run(my_function,NULL,"XXX");
	kpid = get_task_pid(task,PIDTYPE_PID);
	pidt = pid_vnr(kpid);
	
	init_completion(&comple);
	init_waitqueue_entry(&data,task);
	add_wait_queue_exclusive(&comple.wait,&data);

	printk("the value of done of the comple is: %d\n",comple.done);
	
	wait_for_completion(&comple);
	printk("wait_for_completion(&comple) run !!!          -1 <----");
	printk("the value of done of the comple is: %d\n",comple.done);
	
	printk("the pidt of the kthread_run is: %d\n",pidt);
	printk("the current pid is: %d\n",current->pid);

	printk("out try_wait_for_completion_init,\n");

	return 0;
}

static void __exit try_wait_for_completion_exit(void){
	printk("Goodbye try_wait_for_completion.\n");
}


module_init(try_wait_for_completion_init);
module_exit(try_wait_for_completion_exit);

MODULE_LICENSE("GPL");
