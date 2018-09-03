/*
linux/timer.h
kernel/time/tiemr.c
unsigned long __round_jiffies(unsigned long j, int cpu)
根据j进行取整数 jz，使 jz/HZ=整数，如果 jz > j,返回 jz；否则返回j。
*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/timer.h>

static int __init __round_jiffies_init(void){
	unsigned long j = 0;
	unsigned long r0 = 0;
	unsigned long r1 = 0;
	
	printk("the __round_jiffes test begin\n");
	
	j = jiffies;
	r0 = __round_jiffies(j,0);
	r1 = __round_jiffies(j,1);

	printk("the jiffies is: %ld\n",j);
	printk("the result of __round_jiffies(j,0) is: %ld\n",r0);
	printk("the result of __round_jiffies(j,1) is: %ld\n",r1);
	
	printk("out __round_jiffes_init");
	return 0;
}

static void __exit __round_jiffies_exit(void){
	printk("Goodbye __round_jiffes\n");
	return;
}

module_init(__round_jiffies_init);
module_exit(__round_jiffies_exit);

MODULE_LICENSE("GPL");
