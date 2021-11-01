obj-m += chardev.o
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

test:
	sudo dmesg -C
	sudo insmod chardev.ko
	dmesg
	sudo dmesg -C
	sudo mknod /dev/char_dev1 c 239 0
	sudo chmod 777 /dev/char_dev1
	sudo mknod /dev/char_dev2 c 238 0
	sudo chmod 777 /dev/char_dev2
	
	echo "ABOBA1" > /dev/char_dev1
	dmesg
	sudo dmesg -C
	cat /dev/char_dev1
	dmesg
	sudo dmesg -C
	cat /dev/char_dev2
	dmesg	

	sudo dmesg -C
	echo "ABOBA2" > /dev/char_dev2
	dmesg
	sudo dmesg -C
	cat /dev/char_dev1
	dmesg
	sudo dmesg -C
	cat /dev/char_dev2
	dmesg

	sudo dmesg -C
	sudo rm /dev/char_dev1
	sudo rm /dev/char_dev2
	sudo rmmod chardev.ko
	dmesg