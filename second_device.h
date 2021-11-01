#ifndef SECOND_DEVICE_H
#define SECOND_DEVICE_H

static char Message2[BUF_LEN];
static char *Message2_Ptr;
static int Device2_Open=0;

static int device2_open(struct inode *inode, struct file *file)
{
    if (Device2_Open)
        return -EBUSY;

    Device2_Open++;
    Message2_Ptr = Message2;
    try_module_get(THIS_MODULE);
    return SUCCESS;
}

static int device2_release(struct inode *inode, struct file *file)
{
    Device2_Open--;

    module_put(THIS_MODULE);
    return SUCCESS;
}


static ssize_t device2_read(struct file *file, char __user *buffer, size_t length, loff_t *offset)
{
  
  int bytes_read = 0;

    if (*Message2_Ptr == 0)
        return 0;

    while (length && *Message2_Ptr) {

        put_user(*(Message2_Ptr++), buffer++);
        length--;
        bytes_read++;
    }

    printk("Information was read from the device %s", DEVICE2_NAME);

    return bytes_read;
}



static ssize_t device2_write(struct file *file,
            const char __user * buffer, size_t length, loff_t * offset)
{
  int i;

    for (i = 0; i < length && i < BUF_LEN; i++)
        get_user(Message2[i], buffer + i);

    Message2_Ptr = Message2;

    printk("Device %s got new information", DEVICE2_NAME);

    return i;
}

struct file_operations F2ops = {
    .read = device2_read,
    .write = device2_write,
    .open = device2_open,
    .release = device2_release,
};

#endif