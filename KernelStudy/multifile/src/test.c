#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

int test(void)
{
	printk(KERN_ALERT "test file in src folder.\n");
	return 0;
}