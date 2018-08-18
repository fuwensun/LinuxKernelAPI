/*
*/

#include <linux/module.h>
#include <linux/sched.h>
#include <linux/list.h>

static int __init init_waitqueue_head_init(void){
	wait_queue_head_t head;
	printk("into init_waitqueue_head_init.\n");
	
	if(head.head.next == NULL ||  head.head.prev == NULL){
		printk("the head has not been initialized\n");
	}

	init_waitqueue_head(&head);
	if(head.head.next == &head.head && head.head.prev == &head.head){
		printk("the head has been initialized\n");
	}else{
		printk("the head has not been inittailized\n");
	}
	printk("out init_qitqueue_head_init.\n");
	return 0;
}

static void __exit init_waitqueue_head_exit(void){
	printk("Goodbye init_waitqueue_head\n");
}

module_init(init_waitqueue_head_init);
module_exit(init_waitqueue_head_exit);
MODULE_LICENSE("GPL");
