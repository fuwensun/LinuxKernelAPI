/*
asm/atomic.h
static inline void atomic_add(int i, atomic_t *v)
将原子变量*v的值加i。
*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <asm/atomic.h>

atomic_t my_atomic;

static int __init atomic_add_init(void){
	
	int i = 0;
	atomic_set(&my_atomic,5);
	printk("after atomic_set, my_atomic.counter = %d\n",atomic_read(&my_atomic));
	
	i = 3;
	atomic_add(i,&my_atomic);
	printk("after atomic_add,my_atomic.counter = %d\n",atomic_read(&my_atomic));
	return 0;
}

static void __exit atomic_add_exit(void){
	printk("exit!\n");
	return;
}

module_init(atomic_add_init);
module_exit(atomic_add_exit);

MODULE_LICENSE("GPL");
