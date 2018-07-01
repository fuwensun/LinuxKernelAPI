/********************************************************************************
* File Name:	atomic_add.c
* Description:	第8章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/types.h> 
#include <linux/init.h> 
#include <linux/module.h> 
MODULE_LICENSE("GPL"); 
static int __init atomic_add_init(void); 
static void __exit atomic_add_exit(void);

atomic_t my_atomic ;

int __init atomic_add_init(void) 
{	 
	int i;
	atomic_set( &my_atomic, 5 );
	printk("<0>after atomic_set, my_atomic.counter = %d\n", atomic_read( &my_atomic));

	i = 3;
	atomic_add( i, &my_atomic );  //将原子类型的变量my_atomic原子地增加i
	printk("<0>after atomic_add, my_atomic.counter = %d\n", atomic_read( &my_atomic));

	return 0;	
}

void __exit atomic_add_exit(void) 
{ 
	printk("<0>exit!\n");
}

module_init(atomic_add_init); 
module_exit(atomic_add_exit);
