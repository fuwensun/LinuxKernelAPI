/*
 * 
 */

/*x86
//linux\arch\x86\include\asm\thread_info.h
struct thread_info {
	unsigned long		flags;	//low level flags
	u32			status;			//thread synchronous flags
};
*/
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/pid.h>
#include <asm/thread_info.h>

static int __init current_thread_info_init(void){

	struct task_struct *task = NULL;
	struct thread_info *info = NULL;

	printk("into current_thread_info_init.");
	
	printk("the current pid is:%d\n",current->pid);
	
	info = current_thread_info();
//	task = info->task;
	task = current;

	printk("the pid of the thread is:%d\n",task->pid);
	printk("the tgid of the thread is:%d\n",task->tgid);
	printk("the low level flags is:%lu\n",info->flags);
	printk("the thread synchromous flags is:%u\n",info->status);
//	printk("current CPU is:%u\n",info->cpu);
//	printk("the preempt_count is:%d\n",info->preempt_count);

	printk("out current_thread_info_init.");
	return 0;
}

static void __exit current_thread_info_exit(void){
	printk("Goodbye current_thread_info.\n");
}

module_init(current_thread_info_init);
module_exit(current_thread_info_exit);

MODULE_LICENSE("GPL");
