obj-m += chardev.o
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

creation_test:
	sudo dmesg -C
	sudo insmod chardev.ko
	dmesg
	sudo dmesg -C
	sudo rmmod chardev.ko
	dmesg

full_test:
	sudo dmesg -C
	sudo insmod chardev.ko

	sudo mknod /dev/char_dev1 c 239 0
	sudo chmod 777 /dev/char_dev1
	
	sudo mknod /dev/char_dev2 c 239 1
	sudo chmod 777 /dev/char_dev2

	echo "ABOBA1" > /dev/char_dev1
	cat /dev/char_dev1
	cat /dev/char_dev2

	echo "ABOBA2" > /dev/char_dev2
	cat /dev/char_dev1
	cat /dev/char_dev2

	sudo rm /dev/char_dev1
	sudo rm /dev/char_dev2
	sudo rmmod chardev.ko
	dmesg