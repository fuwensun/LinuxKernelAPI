/*
 * linux/pid.h
 * void put_pid(struct pid *pid)
 * 减一进程描述符的引用计数。
 */

#include <linux/module.h>
#include <linux/sched.h>
#include <linux/pid.h>
#include <linux/kthread.h>

int my_function(void *argc){
	printk("in the kernel thread function!\n");
	return 0;
}

static int __init put_pid_init(void){
	pid_t pidt = 0;
	struct task_struct *task = NULL;
	struct pid *kpid = NULL;

	printk("into put_pid_init.\n");
	
	task = kthread_run(my_function,NULL,"xxx");
	kpid = get_task_pid(task,PIDTYPE_PID);
        pidt = pid_nr(kpid);
	
	printk("the count of the pid is:%d\n",kpid->count);
	printk("the level of the pid is:%d\n",kpid->level);
	printk("the pid of the find_get_pid is:%d\n",kpid->numbers[kpid->level].nr);

	put_pid(kpid);
	printk("the new value after the function put_pid:\n");
	printk("the count of the pid is:%d\n",kpid->count);
	printk("the level of the pid is:%d\n",kpid->level);
	printk("the new pid of the kthread is:%d\n",kpid->numbers[kpid->level].nr);

	printk("the pidt of the kthread_run is:%d\n",pidt);
	printk("out put_pid_init.\n");
	
	return 0;
}

static void __exit put_pid_exit(void){
	printk("Goodbye put_pid\n");
}


module_init(put_pid_init);
module_exit(put_pid_exit);

MODULE_LICENSE("GPL");
