#KDIR?=/lib/modules/6.6.51+rpt-rpi-v7/build
KDIR?=/lib/modules/$(shell uname -r)/build/

obj-m+=example.o

all:
	make -C $(KDIR) M=$(PWD) modules
clean:
	make -C $(KDIR) M=$(PWD) clean

#FOR COMPILATION TYPE make example.c IN CMD
#sudo insmod example.ko
#sudo rmmod example.ko


#sudo mknod /dev/example c 505 0
#dmesg command

#strace command
#cat /dev/example
#echo "string" > /dev/example
#struct device *device_create

#ls -l /dev/testCharDevice
#registering in sysfs

#we can find our class in /sys/class/ (example_cl - new class of char device)
#if we enter in this class 'file' we will see our 'device'