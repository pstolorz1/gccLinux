#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Training of loadable super kernel module");
MODULE_AUTHOR("PaSt");

#define FAILURE (-1)
#define SUCCESS (0)
#define DEVICE_NAME "testCharDevice"
#define CLASS_NAME "example_cl"

static dev_t exampleDev;
static struct cdev* example_c_dev;
static struct class* example_cl = NULL;
static struct device* example_device = NULL; 

static ssize_t dev_read(struct file*, char*, size_t, loff_t*);
static ssize_t dev_write(struct file*, const char*, size_t, loff_t*);

static struct file_operations example_fops = {
    .open = NULL,
    .release = NULL,
    .read = dev_read,
    .write = dev_write,
};



static ssize_t dev_read(struct file* file, char* buffer, size_t len, loff_t* offset)
{
    printk(KERN_INFO "Example module: read function was called\n");
    return 0;
}

static ssize_t dev_write(struct file* file, const char* buffer, size_t len, loff_t* offset)
{
    printk(KERN_INFO "Example module: write function was called\n");
    return len;
}



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

    //example_cl = class_create(THIS_MODULE, CLASS_NAME); in newer kernels only CLASS_NAME arg is required
    example_cl = class_create(CLASS_NAME);
    if(IS_ERR(example_cl)){
        printk(KERN_ERR "Error creating example class\n");
        goto error_class_create;
    }

    example_device = device_create(example_cl, NULL, exampleDev, NULL, DEVICE_NAME);
    if(IS_ERR(example_device)){
        printk(KERN_ERR "Error creating and registering device in sysfs\n");
        goto error_device_create;
    }

    printk(KERN_INFO "Example character device added successfully!. Major number: %d\n", MAJOR(exampleDev));
    return SUCCESS;

error_device_create:
    class_destroy(example_cl);
error_class_create:
error_cdev_alloc:
    unregister_chrdev_region(example_c_dev, 1);

error_cdev_add:
    cdev_del(example_c_dev);
    unregister_chrdev_region(example_c_dev, 1);
    return FAILURE;

}

static void __exit exitFoo(void)
{
    device_destroy(example_cl, exampleDev);
    class_destroy(example_cl);
    cdev_del(example_c_dev);
    unregister_chrdev_region(example_c_dev, 1);
    printk(KERN_INFO "Example module: example character device exit\n");
}

module_init(initFoo);
module_exit(exitFoo);
