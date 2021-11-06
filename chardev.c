#include "chardev.h"

#include "first_device.h"
//#include "second_device.h"


int init_module()
{
    int ret_val;

    int i;
    for (i=0; i<DEVICES_KOL; ++i) {
        if (i==0) {
            ret_val = register_chrdev(0, DEVICE_NAME[i], &Fops);
            
            if (ret_val < 0) {
                printk(KERN_ERR "Sorry, registering the character device failed with %d\n", ret_val);
                return ret_val;
            }
        }
        char_dev[i]=MKDEV(ret_val,i);
        
        printk("Registration is a success. The major and minor %s numbers are %d %d.\n",DEVICE_NAME[i], MAJOR(char_dev[i]), MINOR(char_dev[i])); 
    }

    return 0;
}

void cleanup_module()
{
    int i;
    for (i=0; i<DEVICES_KOL; ++i) {
        unregister_chrdev(MAJOR(char_dev[i]), DEVICE_NAME[i]);
    }
    printk("Module removed\n");
}