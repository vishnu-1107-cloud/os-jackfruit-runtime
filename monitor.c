
#include <linux/module.h>
#include <linux/kernel.h>

int init_module(void) {
    printk(KERN_INFO "Jackfruit monitor loaded\n");
    return 0;
}

void cleanup_module(void) {
    printk(KERN_INFO "Jackfruit monitor removed\n");
}

MODULE_LICENSE("GPL");
