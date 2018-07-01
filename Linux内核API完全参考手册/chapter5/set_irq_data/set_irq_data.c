/********************************************************************************
* File Name:	set_irq_data.c
* Description:	第5章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/irq.h>
#include <linux/interrupt.h>
#include <linux/module.h>
#include <linux/hardirq.h>
#include <linux/vmalloc.h>
MODULE_LICENSE("GPL");    
                                  
//自定义中断处理函数
static irqreturn_t irq_handler(int irq,void *dev_id)
{
	printk("<0>the irq is :%d\n",irq);
  	printk("<0>in the interrupt handler function\n");
   	return IRQ_WAKE_THREAD;
}

//自定义中断线程处理函数
static irqreturn_t irq_thread_fn(int irq,void *dev_id)
{
	printk("<0>the irq is :%d\n",irq);
  	printk("<0>in the thread handler function\n");
   	return IRQ_HANDLED;
}

//自定义数据结构，用于函数set_irq_chip_data的第二个参数，作者随意定义，无实际意义
struct  handler_data
{
	int num;
       char * name;
       int flags;
};

static int irq=13;   //1000                         

static int __init set_irq_data_init(void) 
{
	int result=0;
	int result1=0;
	struct handler_data data;
	printk("<0>into set_irq_data_init\n");
	result=request_threaded_irq(irq,irq_handler,irq_thread_fn,IRQF_DISABLED,"A_NEW_DEVICE",NULL);

        /*申请中断，irq 是对应的中断号，myhandler是对应的中断处理函数，mythread_fn是对应的中断线程处理函数，IRQF_DISABLED是中断类型*/	
	result1=set_irq_data(irq,&data);   //调用函数set_irq_data()设置handler_data的值
        
	//显示函数调用结果
	printk("<0>the request_threaded_irq result is: %d\n",result);    	
        printk("<0>the set_irq_data result is: %d\n",result1);
	printk("<0>out set_irq_data_init\n");
	return 0; 
}

static void __exit set_irq_data_exit(void)
{ 
	free_irq(irq,NULL);    //释放申请的中断
	printk("<0>Goodbye set_irq_data\n");
 	return;
}

module_init(set_irq_data_init);
module_exit(set_irq_data_exit);
