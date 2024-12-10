// this a driver for test rsi and other interrupt

//rsi func_id
// SMCCC VERSION 80000000
// SMC32_PSCI_FID_MIN 84000000 SMC32_PSCI_FID_MAX 84000014
// SMC64_PSCI_FID_MIN c4000000 SMC64_PSCI_FID_MAX c4000014
// SMC_RSI_VERSION c4000190
// SMC RSI_FEATURES c4000191
// SMC_RSI_ATTEST_TOKEN_INIT c4000194
// SMC_RSI_ATTEST_TOKEN_CONTINUE c4000195
// SMC_RSI_MEASUREMENT_READ c4000192
// SMC _RSI _MEASUREMENT_EXTEND c4000193
// SMC RSI_REALM CONFIG c4000196
// SMC RSI_IPA_STATE SET c4000197
// SMC_RSI_IPA_STATE_GET c4000198
// SMC _RSI _HOST_CALL c4000199



#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/cdev.h>
#include <linux/arm-smccc.h>

#include "smc_parse.h"
#define DEVICE_NAME "smc_fuzz"
#define IOCTL_SET_MSG _IOR('a', 1, char *)
#define IOCTL_GET_MSG _IOR('a', 2, char *)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("tsl");
MODULE_DESCRIPTION("A simple Linux driver with ioctl support");
MODULE_VERSION("0.1");

static int major;
struct msg msg = {0};
static struct cdev smc_fuzz_cdev;

static int smc_fuzz_open(struct inode *inode, struct file *file) {
    printk(KERN_INFO "smc_fuzz: Device opened\n");
    return 0;
}

static int smc_fuzz_release(struct inode *inode, struct file *file) {
    printk(KERN_INFO "smc_fuzz: Device closed\n");
    return 0;
}

static long smc_fuzz_ioctl(struct file *file, unsigned int cmd, unsigned long arg) {
    switch (cmd) {
        case IOCTL_SET_MSG:
            if (copy_from_user((char*)&msg, (struct msg *)arg, sizeof(msg))) {
                return -EFAULT;
            }
            
            struct arm_smccc_res res = {0};
            smc_parse(&msg.smc_args, &msg.smc_res);
            printk(KERN_INFO "smc_fuzz: func_id set to %ld\n", msg.smc_args.args[0]);
            break;
        case IOCTL_GET_MSG:
            if (copy_to_user((struct msg *)arg, &msg, sizeof(msg))) {
                return -EFAULT;
            }
            printk(KERN_INFO "smc_fuzz: Message sent to user\n");
            break;
        default:
            return -EINVAL;
    }
    return 0;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = smc_fuzz_open,
    .release = smc_fuzz_release,
    .unlocked_ioctl = smc_fuzz_ioctl,
};

static int __init smc_fuzz_init(void) {
    major = register_chrdev(0, DEVICE_NAME, &fops);
    if (major < 0) {
        printk(KERN_ALERT "smc_fuzz: Failed to register a major number\n");
        return major;
    }
    printk(KERN_INFO "smc_fuzz: Registered with major number %d\n", major);

    cdev_init(&smc_fuzz_cdev, &fops);
    smc_fuzz_cdev.owner = THIS_MODULE;
    if (cdev_add(&smc_fuzz_cdev, MKDEV(major, 0), 1) < 0) {
        unregister_chrdev(major, DEVICE_NAME);
        printk(KERN_ALERT "smc_fuzz: Failed to add cdev\n");
        return -1;
    }

    printk(KERN_INFO "smc_fuzz: Initialized\n");
    return 0;
}

static void __exit smc_fuzz_exit(void) {
    cdev_del(&smc_fuzz_cdev);
    unregister_chrdev(major, DEVICE_NAME);
    printk(KERN_INFO "smc_fuzz: Exiting the smc_fuzz driver\n");
}

module_init(smc_fuzz_init);
module_exit(smc_fuzz_exit);