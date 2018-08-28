/*
linux/mm.h
mm/mmap.c
unsigned long get_unmapped_area(struct file *file, unsigned long addr, unsigned long len,unsigned long pgoff, unsigned long flags)

在当前进程的用户空间查找addr所在的未映射的区间，成功返回区间虚拟地址（页面对齐）；失败返回-ENOMEN。

file：要映射的文件。
addr：虚拟空间的地址。
len ：区间长度。
pgoff：文件内偏移。
flags：设置区间的类型。

*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/mm.h>
#include <asm/highmem.h>

static int __init get_unmapped_area_init(void){

	unsigned long len = 0;
	unsigned long addr = 0;
	unsigned long address = 0;

	addr = 0x1fff;
	len = 1025;
	address = get_unmapped_area(NULL,addr,len,0,MM_ANONPAGES);
	printk("find address = 0x%lx\n",address);

	addr = PAGE_OFFSET*2;
	len = 1025;
	address = get_unmapped_area(NULL,addr,len,0,MM_ANONPAGES);
	printk("PAGE_OFFSET  = 0x%16lx\n",PAGE_OFFSET);
	printk("VMALLOC_START= 0x%16lx\n",VMALLOC_START);
	printk("VMALLOC_END  = 0x%16lx\n",VMALLOC_END  );
	//printk("PKMAP_ADDR   = 0x%16lx\n",PKMAP_BASE   );
	printk("FIXADDR_START= 0x%16lx\n",FIXADDR_START);
	printk("find address = 0x%16lx\n",address);

	return 0;
}

static void __exit get_unmapped_area_exit(void){
	printk("exit ok!\n");
}

module_init(get_unmapped_area_init);
module_exit(get_unmapped_area_exit);

MODULE_LICENSE("GPL");
