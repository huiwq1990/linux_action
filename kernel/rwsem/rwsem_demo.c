#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/slab.h>
#include <linux/rcupdate.h>
#include <linux/mutex.h>
#include <linux/rwsem.h>


MODULE_LICENSE("GPL");

#define MAX_KTHREAD 10
static struct task_struct *threads[MAX_KTHREAD];

//static DEFINE_SPINLOCK(threads_lock);
struct our_data{
	int count1;
	int count2;
	struct rcu_head rhead;
};
static struct our_data my_data;
static struct our_data __rcu *pmy_data = &my_data;
static unsigned long reader_bitmap;

static DECLARE_RWSEM(myrwlock);

static void set_reader_number(int reader){
	//WARN_ON((MAX_KTHREAD-reader)!=1);
	reader_bitmap = 0;
	while(reader){
		reader_bitmap |= (1<<--reader);
	}
}
static void reader_do(void)
{
	down_read(&myrwlock);
	printk("read count1:%d count2:%d",pmy_data->count1,pmy_data->count2);
	up_read(&myrwlock);
}

static void writer_do(void)
{
	down_write(&myrwlock);
	pmy_data->count1++;
	pmy_data->count2+=10;
	up_write(&myrwlock);
}

static void show_my_data(void){
	printk("count1 %d, count2 %d\n",pmy_data->count1,pmy_data->count2);
}

static int thread_do(void *data)
{
	long i = (long)data;
	int reader = (reader_bitmap &(1<<i));
	printk("run %ld %s...\n",i,reader?"reader":"writer");
	while(!kthread_should_stop()){
		if(reader){
			reader_do();
		}else{
			writer_do();
		}
		msleep(10);
	}
	return 0;
}

static int create_thread(void)
{
	int i;
	for(i=0;i<MAX_KTHREAD;i++){
		struct task_struct *thread;
		thread = kthread_run(thread_do,(void *)(long)i,"thread-%d",i);
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

static int hello_init(void)
{

	printk(KERN_ALERT "hello,I am edsionte\n");
	set_reader_number(5);
	if(create_thread()){
		goto err;
	}
	return 0;
err:
	cleanup_threads();
	return -1;
}
static void hello_exit(void)
{
	printk(KERN_ALERT "goodbye,kernel\n");
	cleanup_threads();
	show_my_data();
}
module_init(hello_init);
module_exit(hello_exit);

MODULE_AUTHOR("edsionte Wu");
MODULE_DESCRIPTION("This is a simple example!\n");
MODULE_ALIAS("A simplest example");