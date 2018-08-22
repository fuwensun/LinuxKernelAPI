/*
linux/sched.h
kernel/sched/core.c
int set_cpus_allowed_ptr(struct task_struct *p, const struct cpumask *new_mask)
改变一个进程的CPU亲和力。把线程迁移到一个合适的CPU,
如果它之前运行的CPU已经被从allowed bitmask上移除了，那么把它调度开。
*/

#include <linux/module.h>
#include <linux/sched.h>
#include <linux/pid.h>
#include <linux/wait.h>
#include <linux/cpumask.h>
#include <linux/kthread.h>
#include <linux/thread_info.h>
#include <linux/delay.h>


static int cpu;

int my_function(void *argc){
	int data = -1;
	cpumask_var_t mask;
	alloc_cpumask_var(&mask,GFP_KERNEL);
	cpumask_set_cpu(cpu,mask);

	printk("--->in the kernel thread function!\n");
	printk("--->the current pid is: %d\n",current->pid);
	msleep(100);
	data = set_cpus_allowed_ptr(current->real_parent,mask);
	printk("--->the return result of the set_cpus_allowed_ptr is: %d\n",data);
	printk("--->out the kernel thread function!\n");
	return 0;
}

static int __init set_cpus_allowed_ptr_init(void){
	pid_t pidt = 0;
	long result = 0;
	//struct thread_info *info = NULL;
	struct task_struct *task = NULL;
	struct pid *kpid = NULL;

	wait_queue_head_t head;
	wait_queue_entry_t data;

	printk("into set_cpus_allowed_ptr_init!\n");

	printk("the cpu of the current thread is: %d  <---\n",current->cpu);
	//info = current_thread_info();
	task = kthread_run(my_function,NULL,"XXX");
	//task = kthread_run(my_function,NULL,"YYY");
	//task = kthread_run(my_function,NULL,"ZZZ");
	kpid = get_task_pid(task,PIDTYPE_PID);
	pidt = pid_vnr(kpid);

	cpu = (current->cpu < 2) ? 2 : 0;//
	init_waitqueue_head(&head);
	init_waitqueue_entry(&data,current);
	//add_wait_queue(&head,&data);
	prepare_to_wait(&head,&data,TASK_UNINTERRUPTIBLE);
	result = schedule_timeout(200);

	printk("the new cpu of the current thread is: %d  <---\n",current->cpu);
	printk("the return result of the kthread_run is: %d\n",pidt);
	printk("the return result of the schedule_timeout is: %ld\n",result);
	printk("the curent pid is: %d\n",current->pid);
	
	printk("out set_cpus_allowed_ptr_init.\n");
	return 0;
}

static void __exit set_cpus_allowed_ptr_exit(void){
	printk("Goodbye set_cpus_allowed_ptr\n");
}

module_init(set_cpus_allowed_ptr_init);
module_exit(set_cpus_allowed_ptr_exit);

MODULE_LICENSE("GPL");


/*

[ 1925.191933] into set_cpus_allowed_ptr_init!
[ 1925.191935] the cpu of the current thread is: 2  <---
[ 1925.193654] --->in the kernel thread function!
[ 1925.193656] --->the current pid is: 3651
[ 1925.597819] the new cpu of the current thread is: 1 <---
[ 1925.597824] the return result of the kthread_run is: 3651
[ 1925.597826] the return result of the schedule_timeout is: 0
[ 1925.597829] the curent pid is: 3649
[ 1925.597830] out set_cpus_allowed_ptr_init.
[ 1925.726782] --->the return result of the set_cpus_allowed_ptr is: 0
[ 1925.726785] --->out the kernel thread function!
--------------------------------------------------------------------

sfw@u18a ~/github.com/Linux_Kernel_API_Index/ch4/20set_cpus_allowed_ptr (dev) $ sudo insmod set_cpus_allowed_ptr.ko | sudo dmesg -c
[ 2538.002679] into set_cpus_allowed_ptr_init!
[ 2538.002681] the cpu of the current thread is: 2  <---
sfw@u18a ~/github.com/Linux_Kernel_API_Index/ch4/20set_cpus_allowed_ptr (dev) $ sudo rmmod set_cpus_allowed_ptr.ko | sudo dmesg -c
[ 2538.003881] --->in the kernel thread function!
[ 2538.003882] --->the current pid is: 4338
[ 2538.003936] --->in the kernel thread function!
[ 2538.003937] --->the current pid is: 4339
[ 2538.004449] --->in the kernel thread function!
[ 2538.004450] --->the current pid is: 4340
[ 2538.411206] the new cpu of the current thread is: 1  <---
[ 2538.411210] the return result of the kthread_run is: 4340
[ 2538.411213] the return result of the schedule_timeout is: 0
[ 2538.411215] the curent pid is: 4335
[ 2538.411217] out set_cpus_allowed_ptr_init.
[ 2538.540194] --->the return result of the set_cpus_allowed_ptr is: 0
[ 2538.540197] --->out the kernel thread function!
[ 2538.540240] --->the return result of the set_cpus_allowed_ptr is: 0
[ 2538.540242] --->out the kernel thread function!
[ 2538.540267] --->the return result of the set_cpus_allowed_ptr is: 0
[ 2538.540269] --->out the kernel thread function!
[ 2540.775920] Goodbye set_cpus_allowed_ptr

*/
