/*
linux/mm.h
static inline struct vm_area_struct * find_vma_intersection(struct mm_struct * mm, unsigned long start_addr, unsigned long end_addr)
查找 start_addr 和 end_addr 之间的VMA，找到返回VMA地址；否则返回NULL； 
*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/mm.h>
#include <linux/sched.h>
static int __init find_vma_intersection_init(void){
	struct mm_struct *mm = NULL;
	unsigned long mm_start = 0;
	unsigned long start_addr = 0;
	unsigned long end_addr = 0;
	struct vm_area_struct *vma = NULL;

	mm = current->mm;
	mm_start =  mm->mmap->vm_start;
	printk("mm_start = 0x%lx\n",mm_start);
	
	printk("In first situatuin:\n");

	start_addr = mm_start + 1;
	end_addr = mm_start + 10;
	vma = find_vma_intersection(mm,start_addr,end_addr);
	if(vma){
		printk("vma->vm_start = %lx\n",vma->vm_start);
	}else{
		printk("There is no vma exists between start_addr and end_addr!\n");
	}

	printk("In second situatuin:\n");

	start_addr = mm_start - 10;
	end_addr = mm_start - 1;
	vma = find_vma_intersection(mm,start_addr,end_addr);
	if(vma){
		printk("vma->vm_start = %lx\n",vma->vm_start);
	}else{
		printk("There is no vma exists between start_addr and end_addr!\n");
	}
	
	return 0;
}

static void __exit find_vma_intersection_exit(void){
	printk("exit!\n");
	return;
}

module_init(find_vma_intersection_init);
module_exit(find_vma_intersection_exit);

MODULE_LICENSE("GPL");
