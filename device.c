#include "device.h"

static int device_open(struct inode *inode, struct file *file)
{
    int dev_id=MINOR(file->f_path.dentry->d_inode->i_rdev);

    if (Device_Open_Flag[dev_id])
        return -EBUSY;

    Device_Open_Flag[dev_id]++;
    Message_Ptr[dev_id] = Message[dev_id];
    try_module_get(THIS_MODULE);
    return SUCCESS;
}

static int device_release(struct inode *inode, struct file *file)
{
    int dev_id=MINOR(file->f_path.dentry->d_inode->i_rdev);
    
    Device_Open_Flag[dev_id]--;

    module_put(THIS_MODULE);
    return SUCCESS;
}


static ssize_t device_read(struct file *file, 
                    char __user *buffer, size_t length, loff_t *offset)
{
    int dev_id=MINOR(file->f_path.dentry->d_inode->i_rdev);
  

    int bytes_read = 0;

    if (*Message_Ptr[dev_id] == 0)
        return 0;

    while (length && *Message_Ptr[dev_id]) {
        put_user(*(Message_Ptr[dev_id]++), buffer++);
        length--;
        bytes_read++;
    }


    printk("Information was read from the device %s", DEVICE_NAME[dev_id]);

    return bytes_read;
}



static ssize_t device_write(struct file *file,
            const char __user * buffer, size_t length, loff_t * offset)
{
    int dev_id=MINOR(file->f_path.dentry->d_inode->i_rdev);

    int i;

    for (i = 0; i < length && i < BUF_LEN; i++)
        get_user(Message[dev_id][i], buffer + i);

    Message_Ptr[dev_id] = Message[dev_id];

    printk("Device %s got new information", DEVICE_NAME[dev_id]);

    return i;
}