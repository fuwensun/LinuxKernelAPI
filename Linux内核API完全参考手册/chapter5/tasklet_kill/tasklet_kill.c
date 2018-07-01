/********************************************************************************
* File Name:	tasklet_kill.c
* Description:	第5章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/interrupt.h> 
#include <linux/module.h> 
#include <linux/init.h> 
MODULE_LICENSE("GPL");
static unsigned long data=0; 
static struct tasklet_struct tasklet; 

//自定义软中断处理函数，在此只有显示功能
static void irq_tasklet_action(unsigned long data) 
{ 
	printk("<0>in the irq_tasklet_action the state of the tasklet is :%ld\n",(&tasklet)->state); 
  	printk("<0>tasklet running. by author\n"); 
   	return; 
} 

static int  __init tasklet_kill_init(void) 
{ 
  	printk("<0>into tasklet_kill_init\n"); 
	tasklet_init(&tasklet,irq_tasklet_action,data); //初始化一个struct tasklet_struct 变量，即申请一个软中断变量
	printk("<0>the state of the tasklet after tasklet_init is :%ld\n",(&tasklet)->state); //显示软中断状态
	tasklet_schedule(&tasklet);                //将中断变量放入软中断执行队列
	printk("<0>the state of the tasklet after tasklet_schedule is :%ld\n",(&tasklet)->state);   //显示中断当前状态
   	tasklet_kill(&tasklet);                  //杀死中断，恢复先前的状态
	printk("<0>the state of the tasklet after tasklet_kill is :%ld\n",(&tasklet)->state);   //显示杀死之后的中断状态	 
	printk("<0>out tasklet_kill_init\n"); 
	return 0; 
} 

static void  __exit tasklet_kill_exit(void) 
{ 
	printk("<0>Goodbye tasklet_kill\n"); 
 	return; 
} 

module_init(tasklet_kill_init); 
module_exit(tasklet_kill_exit);
