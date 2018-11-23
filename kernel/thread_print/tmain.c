#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/smp.h>
#include <linux/sched.h>
#include <linux/kthread.h>
#include <linux/delay.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hu Yu <hyuuhit@gmail.com>");
MODULE_DESCRIPTION("kthread test");
MODULE_VERSION("0.1");

static int print_pid(void)
{ 
     struct task_struct *task,*p; 
      struct list_head *pos; 
      int count=0; 
      printk("Hello World enter begin:\n"); 
      task=&init_task; 
      list_for_each(pos,&task->tasks)   /*关键*/ 
               {
               p=list_entry(pos, struct task_struct, tasks); 
               count++; 
               printk("%d--->%s\n",p->pid,p->comm); 
               } 
      printk("the number of process is:%d\n",count); 
      return 0; 
}

static int __init my_init(void)
{
    pr_info("init.\n");
    print_pid();
    pr_info("init finish.\n");
    pr_info("=========================================\n");
    return 0;
}

static void __exit my_exit(void)
{
    pr_info("my exit finish.\n");
    pr_info("=========================================\n");
}

module_init(my_init);
module_exit(my_exit);