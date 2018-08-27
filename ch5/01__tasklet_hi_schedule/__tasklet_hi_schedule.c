/*
linux/interrput.h
kernel/softirq.c
void __tasklet_hi_schedule(struct tasklet_struct *t)
注册t到系统（ tasklet_hi_vec 数组），触发软中断。 
*/

#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/init.h>
#include <linux/delay.h>

static unsigned long data = 0;
static struct tasklet_struct tasklet,tasklet1;

static void irq_tasklet_action(unsigned long data){
	printk("===>in irq_tasklet_action the state of the tasklet is: %ld\n",(&tasklet)->state);
	printk("===>tasklet running by author\n");
	return;
}

static void irq_tasklet_action1(unsigned long data){
	printk("===>in irq_tasklet_action1 the state of the tasklet is: %ld\n",(&tasklet1)->state);
	printk("===>tasklet running by author\n");
	return;
}

static int __init __tasklet_hi_schedule_init(void){
	printk("into __tasklet_hi_schedule.\n");

	tasklet_init(&tasklet,irq_tasklet_action,data);
	tasklet_init(&tasklet1,irq_tasklet_action1,data);

	printk("the state of the tasklet is: %ld\n",(&tasklet)->state);
	printk("the state of the tasklet is: %ld\n",(&tasklet1)->state);

	tasklet_schedule(&tasklet);
//	tasklet_schedule(&tasklet1);
//	tasklet_hi_schedule(&tasklet1);
	if (!test_and_set_bit(TASKLET_STATE_SCHED, &tasklet1.state))
		__tasklet_hi_schedule(&tasklet1);

	tasklet_kill(&tasklet);
	tasklet_kill(&tasklet1);

	printk("out __tasklet_hi_schedule.\n");
	return 0;
}

static void __exit __tasklet_hi_schedule_exit(void){
	printk("Goodbye __tasklet_hi_schedule.\n");
	return;
}

module_init(__tasklet_hi_schedule_init);
module_exit(__tasklet_hi_schedule_exit);

MODULE_LICENSE("GPL");
