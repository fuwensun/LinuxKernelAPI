/*
linux/mm.h
mm/mmap.c
struct vm_area_struct *find_vma(struct mm_struct *mm, unsigned long addr)
查找第一个满足 addr<vm_end 的 VMA 的地址，也就是addr所在VMA，找到返回VMA的，否则NULL。
*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/mm.h>
#include <linux/sched.h>

static int __init find_vma_init(void){
	struct mm_struct *mm = NULL;
	unsigned long addr = 0;
	struct vm_area_struct *vma = NULL;

	mm = current->mm;
	addr = mm->mmap->vm_next->vm_start + 1;
	printk("addr = 0x%lx\n",addr);

	vma = find_vma(mm, addr);
	if(vma){
		printk("vm->vm_start = 0x%lx\n",vma->vm_start);
		printk("vm->vm_end   = 0x%lx\n",vma->vm_end);
	}else{
		printk("UNLUCK! You have failed!\n");
	}
	return 0;
}

static void __exit find_vma_exit(void){
	printk("exit!\n");
}

module_init(find_vma_init);
module_exit(find_vma_exit);

MODULE_LICENSE("GPL");
