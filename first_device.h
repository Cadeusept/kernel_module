#ifndef FIRST_DEVICE_H
#define FIRST_DEVICE_H

static char Message1[BUF_LEN];
static char *Message1_Ptr;
static int Device1_Open=0;

static int device1_open(struct inode *inode, struct file *file)
{
    if (Device1_Open)
        return -EBUSY;

    Device1_Open++;
    Message1_Ptr = Message1;
    try_module_get(THIS_MODULE);
    return SUCCESS;
}

static int device1_release(struct inode *inode, struct file *file)
{
    Device1_Open--;

    module_put(THIS_MODULE);
    return SUCCESS;
}


static ssize_t device1_read(struct file *file, char __user *buffer, size_t length, loff_t *offset)
{
  
  int bytes_read = 0;

    if (*Message1_Ptr == 0)
        return 0;

    while (length && *Message1_Ptr) {

        put_user(*(Message1_Ptr++), buffer++);
        length--;
        bytes_read++;
    }

    printk("Information was read from the device %s", DEVICE1_NAME);

    return bytes_read;
}



static ssize_t device1_write(struct file *file,
            const char __user * buffer, size_t length, loff_t * offset)
{
  int i;

    for (i = 0; i < length && i < BUF_LEN; i++)
        get_user(Message1[i], buffer + i);

    Message1_Ptr = Message1;

    printk("Device %s got new information", DEVICE1_NAME);

    return i;
}

struct file_operations F1ops = {
    .read = device1_read,
    .write = device1_write,
    .open = device1_open,
    .release = device1_release,
};

#endif