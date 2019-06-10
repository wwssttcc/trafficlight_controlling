obj-m := hc595_drv.o
KDIR := /home/bzm/Project/MYD-Y6ULX-devel/04-Source/MYiR-iMX-Linux
all:
		make -C $(KDIR) M=$(PWD) modules CROSS_COMPILE=arm-poky-linux-gnueabi-	ARCH=arm

clean:
		rm -f *.ko *.o *.mod.o *.mod.c *.symvers *.bak *.order