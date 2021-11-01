#ifndef CHARDEV_H
#define CHARDEV_H

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

 
dev_t char_dev1;
dev_t char_dev2;


#define SUCCESS 0
#define DEVICE1_NAME "char_dev1"
#define DEVICE2_NAME "char_dev2"
#define BUF_LEN 80


#endif