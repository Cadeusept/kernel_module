#ifndef CHARDEV_H
#define CHARDEV_H

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define SUCCESS 0
#define DEVICES_KOL 2
#define DEVICE1_NAME "char_dev1"
#define DEVICE2_NAME "char_dev2"
#define BUF_LEN 80
 
dev_t char_dev[DEVICES_KOL];

const char* DEVICE_NAME[DEVICES_KOL]={DEVICE1_NAME, DEVICE2_NAME};

#endif