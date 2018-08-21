/*
linux/sched.h
kernel/sched/core.h
int sched_setscheduler(struct task_struct *p, int policy, const struct sched_param *param)
设置进程的调度策略，要设置的进程p，要设置的策略policy，要设置的实时策略param
*/

/**
 * sched_setscheduler - change the scheduling policy and/or RT priority of a thread.
 * @p: the task in question.
 * @policy: new policy.
 * @param: structure containing the new RT priority.
 *
 * Return: 0 on success. An error code otherwise.
 *
 * NOTE that the task may be already dead.
 */

#include <linux/module.h>
#include <linux/sched.h>
#include <linux/kthread.h>
#include <linux/pid.h>
#include <linux/sched/types.h>
#include <uapi/linux/sched.h>

int my_function(void *argc){
	printk("--->in the kernel thread function!\n");
	printk("--->the policy of current thread is: %d\n",current->policy);
	printk("--->the rt_priority of current thread is: %d\n",current->rt_priority);
	printk("--->the current pid is: %d\n",current->pid);
	printk("--->out the kernel thread function\n");
	return 0;
}

static int __init sched_setscheduler_init(void){
	pid_t pidt = 0;
	int result = 0;
	struct task_struct *task = NULL;
	struct pid *kpid = NULL;
	struct sched_param param;

	printk("into sched_setscheduler_init!\n");

	task = kthread_run(my_function,NULL,"XXX");
	kpid = get_task_pid(task,PIDTYPE_PID);
	pidt = pid_vnr(kpid);

	//iparam.sched_priority = 100;			//#define	EINVAL		22	/* Invalid argument */
	param.sched_priority = SCHED_RR;
	printk("the policy of the child thread is: %d\n",task->policy);
	printk("the rt_prioryty of the child thread is: %d\n",task->rt_priority);

	result = sched_setscheduler(task,1,&param);
	printk("the new policy of the child thread is: %d\n",task->policy);
	printk("the new rt_priority of teh child thread is: %d\n",task->rt_priority);

	printk("the pidt of the kthread_run is: %d\n",pidt);
	printk("the result of the sched_setscheduler is: %d\n",result);
	printk("the current pid is: %d\n",current->pid);

	printk("out sched_setscheduler_init!\n");
	return 0;
}

static void __exit sched_setscheduler_exit(void){
	printk("Goodbye sched_setscheduler\n");
}

module_init(sched_setscheduler_init);
module_exit(sched_setscheduler_exit);
MODULE_LICENSE("GPL");
