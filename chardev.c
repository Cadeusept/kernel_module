#include "chardev.h"

#include "first_device.h"
#include "second_device.h"


int init_module()
{
    int ret_val;

    ret_val = register_chrdev(0, DEVICE1_NAME, &F1ops);

    if (ret_val < 0) {
        printk(KERN_ERR "Sorry, registering the character device failed with %d\n", ret_val);
        return ret_val;
    }

    char_dev1=MKDEV(ret_val,0);
    char_dev2=MKDEV(ret_val,1);

    printk("Registration of device %s is a success. The major and minor numbers are %d %d.\n",DEVICE1_NAME, MAJOR(char_dev1), MINOR(char_dev1));
    printk("Registration of device %s is a success. The major and minor numbers are %d %d.\n",DEVICE2_NAME, MAJOR(char_dev2), MINOR(char_dev2));

    return 0;
}

void cleanup_module()
{
    unregister_chrdev(MAJOR(char_dev1), DEVICE1_NAME);
    unregister_chrdev(MAJOR(char_dev2), DEVICE2_NAME);
    
    printk("Module removed\n");
}