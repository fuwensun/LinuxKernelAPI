/*
linux/vmalloc.h
static inline size_t get_vm_area_size(const struct vm_struct *area)
获取area的虚拟空间大小。
 */

#include <linux/kernel.h>
#include <linux/module.h>
//#include <linux/mm.h>
#include <linux/vmalloc.h>

unsigned long  size = 8192;
struct vm_struct *vm = NULL;

static int __init get_vm_area_size_init(void){
	vm = alloc_vm_area(size,NULL);	
	if(!vm){
		printk("alloc failed!\n");
	}else{
		printk("vm->size = %ld\n",vm->size);
		
		size_t actual_size = get_vm_area_size(vm);
		printk("actual_size = %ld\n",actual_size);
		printk("PAGE_SIZE   = %ld\n",PAGE_SIZE);
	}
	return 0;
}

static void __exit get_vm_area_size_exit(void){
	if(vm){
		free_vm_area(vm);
		printk("exit !\n");
	}
	return;
}

module_init(get_vm_area_size_init);
module_exit(get_vm_area_size_exit);

MODULE_LICENSE("GPL");
