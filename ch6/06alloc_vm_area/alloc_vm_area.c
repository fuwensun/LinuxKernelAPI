/*
linux/vmalloc.h
mm/vmalloc.c
struct vm_struct *alloc_vm_area(size_t size, pte_t **ptes);

struct vm_struct：非连续内存区描述符，表示一段内核虚拟地址空间，位于 [VMALLOC_START,VMALLOC_END]。

分配一段内核虚拟地址空间，大小 size(sfw** 必须是PAGESIZE的整数倍)，建立的页表项 ptes。
失败返回NULL，成功返回描述符地址。
*/

/* Allocate a 'vmalloc' VM area. */

/**
 *	alloc_vm_area - allocate a range of kernel address space
 *	@size:		size of the area
 *	@ptes:		returns the PTEs for the address space
 *
 *	Returns:	NULL on failure, vm_struct on success
 *
 *	This function reserves a range of kernel address space, and
 *	allocates pagetables to map that range.  No actual mappings
 *	are created.
 *
 *	If @ptes is non-NULL, pointers to the PTEs (in init_mm)
 *	allocated for the VM area are returned.
 */


#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/vmalloc.h>
#include <asm/page.h>
#include <asm/pgalloc.h>

pte_t *pte = NULL;
struct vm_struct *vm = NULL;
unsigned long size = PAGE_SIZE*1; //sfw** 必须是PAGESIZE的整数倍

static int __init alloc_vm_area_init(void){
	
	pte = kmalloc(sizeof(pte_t),GFP_KERNEL);
	if(!pte){
		printk("pte alloc failed!\n");
		return 0;
	}
	vm = alloc_vm_area(size,&pte);
	if(!vm){
		printk("alloc failed!\n");
	}else{
		printk("vm->addr = 0x%lx\n",(unsigned long)vm->addr);
		printk("vm->size = %ld\n",vm->size);
		printk("page_size = %ld\n",PAGE_SIZE);
	}
	return 0;
}

static void __exit alloc_vm_area_exit(void){
	if(vm){
		free_vm_area(vm);
		printk("free_vm_area ok!\n");
	}
	printk("exit !\n");
}

module_init(alloc_vm_area_init);
module_exit(alloc_vm_area_exit);
MODULE_LICENSE("GPL");

