/********************************************************************************
* File Name:	round_jiffies.c
* Description:	第7章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/module.h> 
#include<linux/timer.h>
MODULE_LICENSE("GPL");

int __init round_jiffies_init(void) 
{
	printk("the round_jiffies test begin\n");
	unsigned long j=jiffies; //记录当前节拍 	
	unsigned long __result1=__round_jiffies(j,0); //参数j当前节拍，0是cpu编号
	unsigned long __result2=__round_jiffies(j,1);//参数j当前节拍，1是cpu编号
	unsigned long result1=round_jiffies(j);//参数j当前节拍
	unsigned long result2=round_jiffies(j);//参数j当前节拍
	printk("the jiffies is :%ld\n",j);//显示当前节拍
    	//显示函数调用结果	
	printk("the __result1 of __round_jiffies(j,0) is :%ld\n",__result1);
	printk("the __result2 of __round_jiffies(j,1) is :%ld\n",__result2);
	printk("the result1 of round_jiffies(j) is :%ld\n",result1);
	printk("the result2 of round_jiffies(j) is :%ld\n",result2); 
	printk("<0>out round_jiffies_init");
	return 0; 
} 

void __exit round_jiffies_exit(void) 
{        
	printk("<0>Goodbye round_jiffies\n"); 
}

module_init(round_jiffies_init);
module_exit(round_jiffies_exit); 
