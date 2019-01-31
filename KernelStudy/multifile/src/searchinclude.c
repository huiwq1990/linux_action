#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

int searchinclude(void)
{
	printk(KERN_ALERT "searchinclude.\n");
	return 0;
}