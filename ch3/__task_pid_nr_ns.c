/*
 */

#include <linux/module.h>
#include <linux/sched.h>
#include <linux/pid.h>
#include <linux/sched/task.h>									//<---1
#include <linux/kthread.h>
//在include/linux/sched.h中定义了一个特殊标志CLONE_KERNEL供kernel_thread使用。
#define CLONE_KERNEL    (CLONE_FS | CLONE_FILES | CLONE_SIGHAND)

/*

 struct upid is used to get the id of the struct pid, as it is
 seen in particular namespace. Later the struct pid is found with
 find_pid_ns() using the int nr and struct pid_namespace *ns.

struct upid {
	int nr;
	struct pid_namespace *ns;
};


struct pid
{
	atomic_t count;
	unsigned int level;
	struct hlist_head tasks[PIDTYPE_MAX];
	struct rcu_head rcu;
	struct upid numbers[1];
};

pid_t pid_nr_ns(struct pid *pid, struct pid_namespace *ns)
{
	struct upid *upid;
	pid_t nr = 0;

	if (pid && ns->level <= pid->level) {
		upid = &pid->numbers[ns->level];
		if (upid->ns == ns)
			nr = upid->nr;
	}
	return nr;
}

pid_t pid_vnr(struct pid *pid)
{
	return pid_nr_ns(pid, task_active_pid_ns(current));
}


pid_t kernel_thread(int (*fn)(void *), void *arg, unsigned long flags);
struct pid *find_get_pid(int nr);
struct task_struct *pid_task(struct pid *pid, enum pid_type type);
*/


int my_function(void *argc){
	printk("in the kernel thread function!\n");
	return 0;
}

static int __init __task_pid_nr_ns_init(void){
	pid_t result = 0;
	pid_t result1 = 0;
	struct pid *kpid = NULL;
	struct task_struct *task = NULL;

	printk("into __task_pid_nr_ns_init.\n");

	//result = kernel_thread(my_function,NULL,CLONE_KERNEL);	//<---1
	result = kthread_run(my_function,NULL,"xx");	//<---1

	kpid = find_get_pid(result);

	task = pid_task(kpid,PIDTYPE_PID);

	result1 = __task_pid_nr_ns(task,PIDTYPE_PID,0); //kpid->numbers[kpid->level].ns);

//	printk("the pid of the find_get_pid is: %d\n",kpid->numbers[0]);
//	printk("the result of the __task_pid_nr_ns is: %d\n",result1);
	printk("the result of the kernel_thread is: %d\n",result);
	printk("the pid of current thread is: %d\n",current->pid);
	
	printk("out __task_pid_nr_ns_init.\n");
	return 0;
}

static void __exit __task_pid_nr_ns_exit(void){
	printk("Goodbye __task_pid_nr_ns\n");
}

module_init(__task_pid_nr_ns_init);
module_exit(__task_pid_nr_ns_exit);

MODULE_LICENSE("GPL");

