/*
 * linux/kernel/pid.c
 * struct pid *find_get_pid(int nr)
 * 根据进程号获取进程描述符，并加一其count字段
 */


#include <linux/module.h>
#include <linux/sched.h>
#include <linux/pid.h>
#include <linux/kthread.h>

int my_function(void *argc){
	printk("in the kernel thread function!\n");
	return 0;
}

static int __init find_get_pid_init(void){
	int result = 0;
	struct pid *kpid = NULL;		
	struct task_struct *task = NULL; //进程描述符

	printk("into find_get_pid_init.\n");

	task = kthread_run(my_function,NULL,"XXX");
	result = task->pid;
	kpid = find_get_pid(result);

	printk("the count of the pid is:%d\n",kpid->count);
	printk("the level of the pid is:%d\n",kpid->level);

	//显示进程号，find_get_pid 返回 kpid->numbers[kpid->level].nr
	printk("the pid Of the find_get_pid is: %d\n",kpid->numbers[kpid->level].nr);
	printk("the result of the kthread_run is: %d\n",result);

	return 0;
}

static void __exit find_get_pid_exit(void){
	printk("Goodbye find_get_pid\n");
}

module_init(find_get_pid_init);
module_exit(find_get_pid_exit);

MODULE_LICENSE("GPL");
