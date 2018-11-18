#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

int adder(int a,int b)
{
	int ret = a+b;
		printk("adder=%d\n",ret);
	return ret;
}
EXPORT_SYMBOL(adder);