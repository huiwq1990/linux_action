#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/delay.h>


MODULE_LICENSE("GPL");

#define MAX_KTHREAD 10
static struct task_struct *threads[MAX_KTHREAD];

//static DEFINE_SPINLOCK(threads_lock);
static spinlock_t threads_lock;
static void threads_lock_init(void)
{
	spin_lock_init(&threads_lock);
}
struct our_data{
	int count1;
	int count2;
};
static struct our_data my_data;

static void show_my_data(void){
	printk("count1 %d, count2 %d\n",my_data.count1,my_data.count2);
}

static int thread_do(void *data)
{
	printk("run ...\n");
	while(!kthread_should_stop()){
		msleep(10);
		spin_lock(&threads_lock);
		my_data.count1 += 1;
		my_data.count2 += 10;
		spin_unlock(&threads_lock);	
	}
	return 0;
}

static int create_thread(void)
{
	int i;
	for(i=0;i<MAX_KTHREAD;i++){
		struct task_struct *thread;
		thread = kthread_run(thread_do,NULL,"thread-%d",i);
		if(IS_ERR(thread)){
			return -1;
		}
		threads[i] = thread;
	}
	return 0;
}

static void cleanup_threads(void)
{
	int i;
	for(i=0;i<MAX_KTHREAD;i++){
		if(threads[i]){
			kthread_stop(threads[i]);
		}
	}
}

//模块加载函数
static int hello_init(void)
{
	printk(KERN_ALERT "hello,I am edsionte\n");
	threads_lock_init();
	if(create_thread()){
		goto err;
	}
	return 0;
err:
	cleanup_threads();
	return -1;
}
//模块卸载函数
static void hello_exit(void)
{
	printk(KERN_ALERT "goodbye,kernel\n");
	cleanup_threads();
	show_my_data();
}
//模块注册
module_init(hello_init);
module_exit(hello_exit);
//可选
MODULE_AUTHOR("edsionte Wu");
MODULE_DESCRIPTION("This is a simple example!\n");
MODULE_ALIAS("A simplest example");