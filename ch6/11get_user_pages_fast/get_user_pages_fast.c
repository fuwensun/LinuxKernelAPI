/*
linux/mm.h
mm/gup.c
int get_user_pages_fast(unsigned long start, int nr_pages, int write,
			struct page **pages)

sfw**  get_user_pages_fast从内核远程持有用户空间的页，get操作必须对应put操作。
 get_user_pages_fast() - 把用户空间页固定在内存中（阻止swap到硬盘交换区）。
 @start：用户空间起始地址（目标）。
 @nr_pages: 从start起要固定的页数。
 @write:页是否用来写。
 @pages：指向被固定的页的指针的数组。最少应该 nr_pgaes 长。如果调用者只是想确认页
 	已经被固定可以是NULL。（输出参数）
*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/mm.h>
#include <linux/mm_types.h>

static int __init get_user_pages_fast_init(void){
	
	struct page *pages_arry[100];
	struct page **pages = pages_arry;

	struct page *pages1 = NULL;
	
	struct mm_struct *mm = NULL;
	unsigned long addr = 0;
	int len = 0;
	unsigned int gup_flags = 0;
	int locked = 1;
	int ret = 0;
	
	mm = current->mm;
	addr = mm->mmap->vm_start;
	len = vma_pages(mm->mmap);
	gup_flags = 0;
	
	printk("vma_pages(mm->pages) = %d\n",len);
	printk("address of pages is: 0x%lx\n",(unsigned long)pages);
	printk("address of pages1 is: 0x%lx\n",(unsigned long)pages1);
	
	down_read(&current->mm->mmap_sem);
	ret = get_user_pages_fast(addr,len,1,pages);//ok
	up_read(&current->mm->mmap_sem);

	printk("ret = %d\n",ret);
	if(ret > 0){
		printk("page_count(pages)) = %d\n",page_count(*pages));
		printk("address of pages is: 0x%lx\n",(unsigned long)pages);
	}


	//-----
	down_read(&current->mm->mmap_sem);
	ret = get_user_pages_fast(addr,len,gup_flags,&pages1);//ok
	up_read(&current->mm->mmap_sem);

	printk("ret = %d\n",ret);
	if(ret > 0){
		printk("page_count(pages1)) = %d\n",page_count(pages1));
		printk("address of pages1 is: 0x%lx\n",(unsigned long)pages1);
	}	
	return 0;
}

static void __exit get_user_pages_fast_exit(void){
	printk("exit ok!\n");
	return;
}

module_init(get_user_pages_fast_init);
module_exit(get_user_pages_fast_exit);

MODULE_LICENSE("GPL");
