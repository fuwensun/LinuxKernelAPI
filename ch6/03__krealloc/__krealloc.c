/*
linux/slab.h
mm/slab_common.c
void *__krealloc(const void *p, size_t new_size, gfp_t flags)
为虚拟地址p开始newsize大小的空间，以flags的方式从新分配内存，空间的内容不变。
*/
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/mm.h>

#define size 26
struct data{
	char ch[size];
};


#define new_size (sizeof(struct data)+10)
char  *addr = NULL, *addr1 = NULL;

int __init __krealloc_init(void){
	char *temp, *addr, *addr1;
	char x;
	int i = 0;
	
	addr = kmalloc(sizeof(struct data),GFP_KERNEL); 
	if(!addr){
		printk("alloc failed!\n");
		return -ENOMEM;
	}else{
		temp = ((struct data *)addr)->ch;
		*temp = 'a';
		for(i = 0; i < size; i++){
			x = *temp;
			temp++;
			*temp = x+1;
		}
		
		addr1 = __krealloc(addr,new_size,GFP_KERNEL);
		temp = ((struct data *)addr1)->ch;

		printk("addr = 0x%lx\n",(unsigned long)addr);
		printk("addr1 = 0x%lx\n",(unsigned long)addr1);
		printk("addr1 = %c\n",*temp);
		printk("addr1+4 = %c\n",*(temp+4));
		for(i = 0; i < new_size;i++,temp++){
			printk("%c",*temp);
		}

	}

	return 0;
	
}

void __exit __krealloc_exit(void){
	if(!addr){
		kfree(addr);
		printk("free addr!\n");
	}
	if(!addr1){
		kfree(addr1);
		printk("free addr1!\n");
	}
	printk("exit!\n");
}

module_init(__krealloc_init);
module_exit(__krealloc_exit);

MODULE_LICENSE("GPL");
