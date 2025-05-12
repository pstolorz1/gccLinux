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