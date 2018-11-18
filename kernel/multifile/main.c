#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include "include/dirinclude.h"
#include <searchinclude.h>
// implicit declaration of function ‘other’
#include "other.h"
int other(void);
int dirinclude(void);
int searchinclude(void);

extern int test(void);

//必选
//模块许可声明
MODULE_LICENSE("GPL");
//模块加载函数
static int hello_init(void)
{
	other();
	test();
	dirinclude();
	searchinclude();
	return 0;
}
//模块卸载函数
static void hello_exit(void)
{
	printk(KERN_ALERT "goodbye,kernel\n");
}
//模块注册
module_init(hello_init);
module_exit(hello_exit);
//可选
MODULE_AUTHOR("edsionte Wu");
MODULE_DESCRIPTION("This is a simple example!\n");
MODULE_ALIAS("A simplest example");