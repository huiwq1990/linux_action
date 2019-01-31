#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/list.h>
#include <linux/vmalloc.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("XIYOU");

unsigned char * pagemem;
unsigned char *kmallocmem;
unsigned char *vmallocmem;

int minit_module(void)
{
    //pagemem = get_free_page(0);
    printk("<1>pagemem=%s",pagemem);
    kmallocmem = kmalloc(100,0);
    printk("<!>kmallocmem=%s",kmallocmem);
    vmallocmem=vmalloc(1000000);
    printk("vmallocmem=%s",vmallocmem);
    return 0;
}
static void mexit_module(void)
{
    free_page(pagemem);
    kfree(kmallocmem);
    vfree(vmallocmem);
}
module_init(minit_module);
module_exit(mexit_module);