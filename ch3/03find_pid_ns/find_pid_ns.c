/*
 * linux/kernel/pid.c
 * struct pid *find_pid_ns(int nr, struct pid_namespace *ns)
 * 获取进程号nr，命名空间ns，的进程pid。
 */

#include <linux/module.h>
#include <linux/sched.h>
#include <linux/pid.h>
#include <linux/kthread.h>

int my_function(void *argc){
	printk("in the kernel thread function!\n");
	return 0;
}

static int __init find_pid_ns_init(void){
	
	pid_t result = 0;
	struct pid *kpid = NULL;
	struct task_struct *task = NULL;
	struct pid *fpid = NULL;

	task = kthread_run(my_function,NULL,"xxx");
	result = task->pid;
	kpid = find_get_pid(result);
	
	fpid = find_pid_ns(kpid->numbers[kpid->level].nr, kpid->numbers[kpid->level].ns);

	printk("the find_pid_ns result's count is: %d\n", fpid->count);
	printk("the find_pid_ns result's level is: %d\n", fpid->level);

	printk("the find_pid_ns result's pid is: %d\n", fpid->numbers[fpid->level].nr);
	printk("the kthread_run result is: %d\n", result);

	printk("out find_pid_ns_init.\n");

	return 0;
}

static void __exit find_pid_ns_exit(void){
	printk("Goodbye find_pid_ns\n");
}

module_init(find_pid_ns_init);
module_exit(find_pid_ns_exit);

MODULE_LICENSE("GPL");
