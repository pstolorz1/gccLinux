#include <linux/kernel.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Training of loadable super kernel module");
MODULE_AUTHOR("PaSt");

static int __init initFoo(void)
{
    printk(KERN_INFO "Witam i zapraszam do Linux Kernela na RPI Zero\n");
    return 0;
}

static void __exit exitFoo(void)
{
    printk(KERN_INFO "Bye bye, jutro niestety zamkniete\n");
}

module_init(initFoo);
module_exit(exitFoo);
