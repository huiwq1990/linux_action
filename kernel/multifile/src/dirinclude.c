#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

int dirinclude(void)
{
	printk(KERN_ALERT "dir.\n");
	return 0;
}