/*
 * linux/pid.h
 * pid_t pid_vnr(struct pid *pid)
 * 根据进程描述符获得“局部进程号”。
 */

#include <linux/module.h>
#include <linux/sched.h>
#include <linux/pid.h>
#include <linux/kthread.h>

int my_function(void *argc){
	printk("in the kernel thread function\n");
	printk("the current pid is:%d\n",current->pid);
	printk("the current tgid is:%d\n",current->tgid);
 	printk("out the kernel thread function\n");
	return 0;
}

static int __init pid_vnr_init(void){
	pid_t pidt = 0;
	pid_t vpidt = 0;
	struct pid *kpid = NULL;
	struct task_struct *task = NULL;

	printk("into pid_vnr_init.\n");
	task = kthread_run(my_function,NULL,"xxx");
	kpid = get_task_pid(task,PIDTYPE_PID);
	pidt = pid_nr(kpid);

	printk("the level of the pid is:%d\n",kpid->level);
	printk("the pidt of the pid is:%d\n",kpid->numbers[kpid->level].nr);

	vpidt = pid_vnr(kpid);
	printk("the pid_vnr reuslt is:%d\n",vpidt);
	printk("the current pid is:%d\n",current->pid);
	printk("the current tgid is:%d\n",current->tgid);
	printk("out pid_vnr_init.\n");
	return 0;
}

static void __exit pid_vnr_exit(void){
	printk("Goodbye pid_vnr\n");
}

module_init(pid_vnr_init);
module_exit(pid_vnr_exit);

MODULE_LICENSE("GPL");
