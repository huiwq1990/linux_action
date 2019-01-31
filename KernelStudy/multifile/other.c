#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

int other(void)
{
	printk(KERN_ALERT "hello, I'm func in other file.\n");
	return 0;
}