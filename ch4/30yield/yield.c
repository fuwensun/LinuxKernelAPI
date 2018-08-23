// yield();	//官方禁止使用这个API 

#include <linux/module.h> 
#include <linux/sched.h> 
#include <linux/pid.h> 
#include <linux/kthread.h>


MODULE_LICENSE("GPL"); 
 
int my_function(void * argc) 
{ 
    printk("--->in the kernel thread function!\n");   
    printk("--->the current pid is:%d\n",current->pid); 
    printk("--->out the kernel thread function\n"); 
    return 0; 
} 
 

static int __init yield_init(void) 
{    
    struct task_struct *result = NULL;  
    printk("into yield_init.\n");                 
    result=kthread_run(my_function,NULL,"XXX");       
    yield();	//官方禁止使用这个API 
    printk("the result of the kernel_thread is :%d\n",result->pid); 
    printk("the current pid is:%d\n",current->pid); 
    printk("out yield_init.\n"); 
    return 0; 
} 
 

static void __exit yield_exit(void) 
{    
        printk(" Goodbye yield\n");    
} 
 
module_init(yield_init);
module_exit(yield_exit);
