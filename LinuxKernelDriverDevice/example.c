#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/fs.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Training of loadable super kernel module");
MODULE_AUTHOR("PaSt");

#define FAILURE (-1)
#define SUCCESS (0)
#define DEVICE_NAME "testCharDevice"

static dev_t exampleDev;
static struct cdev* example_c_dev;
static struct file_operations example_fops = {
    .open = NULL,
    .release = NULL,
    .read = NULL,
    .write = NULL,
};

static int __init initFoo(void)
{
    printk(KERN_INFO "Example module: example character device init\n");

    if(alloc_chrdev_region(&exampleDev, 0, 1, DEVICE_NAME) < 0)
    {
        printk(KERN_ERR "Example character device init failure\n");
        return FAILURE;
    }

    example_c_dev = cdev_alloc();
    if(example_c_dev == NULL)
    {
        printk(KERN_ERR "Example character device allocation failure\n");
        goto error_cdev_alloc;
    }

    cdev_init(example_c_dev, &example_fops);
    if(cdev_add(example_c_dev, exampleDev, 1) < 0)
    {
        printk(KERN_ERR "Example character device adding failure\n");
        goto error_cdev_add;
    }

    printk(KERN_INFO "Example character device added successfully!. Major number: %d\n", MAJOR(exampleDev));
    return SUCCESS;


error_cdev_alloc:
    unregister_chrdev_region(example_c_dev, 1);
    return FAILURE;

error_cdev_add:
    cdev_del(example_c_dev);
    unregister_chrdev_region(example_c_dev, 1);
    return FAILURE;
}

static void __exit exitFoo(void)
{
    cdev_del(example_c_dev);
    unregister_chrdev_region(example_c_dev, 1);
    printk(KERN_INFO "Example module: example character device exit\n");
}

module_init(initFoo);
module_exit(exitFoo);
