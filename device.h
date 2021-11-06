#ifndef FIRST_DEVICE_H
#define FIRST_DEVICE_H

static char Message[DEVICES_KOL][BUF_LEN];
static char *Message_Ptr[DEVICES_KOL];
static int Device_Open_Flag[DEVICES_KOL]={0};

static int device_open(struct inode *inode, struct file *file);

static int device_release(struct inode *inode, struct file *file);

static ssize_t device_read(struct file *file, 
                    char __user *buffer, size_t length, loff_t *offset);

static ssize_t device_write(struct file *file,
            const char __user * buffer, size_t length, loff_t * offset);

struct file_operations Fops = {
    .read = device_read,
    .write = device_write,
    .open = device_open,
    .release = device_release,
};

#include "device.c"

#endif
