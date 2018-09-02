/*
linux/string.h
mm/util.c
void *memdup_user(const void __user *src, size_t len)
复制一段用户空间内存，地址src长度len，到内核空间。
失败返回ERR_PTR(),要用IS_ERR()判断；成功返回虚拟地址，分配的内存是物理连续的，用kfree释放。
*/

/**
 * memdup_user - duplicate memory region from user space
 *
 * @src: source address in user space
 * @len: number of bytes to copy
 *
 * Returns an ERR_PTR() on failure.  Result is physically
 * contiguous, to be freed by kfree().
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/string.h>
#include <linux/sched.h>

#define len 20

static int __init memdup_user_init(void){
	struct mm_struct *mm = NULL;
	unsigned long mm_start = 0;
	unsigned long *addr = NULL;
	unsigned long *temp = NULL;
	int i = 0;

	mm = current->mm;
	mm_start = mm->mmap->vm_start;
	printk("mm_start = 0x%p\n",(void *)mm_start);
	
	addr = memdup_user((void *)mm_start,len);
	if(IS_ERR(addr)){
		printk("memdup_user failed!\n");
		return -ENOMEM;
	}

	printk("addr = 0x%p\n",addr);
	printk("*addr = %lx\n",*addr); 
	printk("*addr+1 = %lx\n",*(addr+1)); 

	temp = addr;
	for(i = 0; i< len/4; i++,temp++){
		printk("%lx\n",*temp);
	}
	return 0;
}

static void __exit memdup_user_exit(void){
	printk("exit ok!");
	return;
}

module_init(memdup_user_init);
module_exit(memdup_user_exit);

MODULE_LICENSE("GPL");
