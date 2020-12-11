gpio_test.c

#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/gpio.h>

#define GPIO 23

static int __init ofd_init(void)
{
	gpio_is_valid(GPIO);
	gpio_direction_output(GPIO,1);
	printk(KERN_INFO "GPIO-23 driver registered");
	return 0;
}

static void __exit ofd_exit(void)
{
	gpio_is_valid(GPIO);
	gpio_direction_output(GPIO,0);
	printk(KERN_INFO "GPIO-23 driver ungregistered");
}

module_init(ofd_init);
module_exit(ofd_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Dept. CE, KIT");
MODULE_DESCRIPTION("Device Driver Example 2");

