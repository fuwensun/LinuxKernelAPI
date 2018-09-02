/*
linux/string.h
mm/util.c
char *kstrdup(const char *s, gfp_t gfp)
拷贝s到新的以gfg方式分配的内存。
*/

/**
 * kstrdup - allocate space for and copy an existing string
 * @s: the string to duplicate
 * @gfp: the GFP mask used in the kmalloc() call when allocating memory
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/string.h>

static int __init kstrdup_init(void){
	const char *s = "hello world!";
	char *addr = kstrdup(s,GFP_KERNEL);
	char *temp = NULL;

	printk("addr = 0x%lx\n",(unsigned long)addr);
	printk("*addr = %c\n",*addr);
	printk("*addr+4 = %c\n",*(addr+4));
	
	for(temp = addr; *temp != '\0'; temp++)
		printk("%c",*temp);
	return 0;
}

static void __exit kstrdup_exit(void){
	printk("exit ok!\n");
	return;
}

module_init(kstrdup_init);
module_exit(kstrdup_exit);

MODULE_LICENSE("GPL");
