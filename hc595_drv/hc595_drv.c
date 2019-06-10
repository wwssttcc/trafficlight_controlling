#include <linux/module.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <linux/gpio.h>
#include <linux/delay.h>

#define IMX_GPIO_NR(bank, nr)		(((bank) - 1) * 32 + (nr))

#define HC595_DS		IMX_GPIO_NR(1, 5)
#define HC595_OE		IMX_GPIO_NR(1, 4)
#define HC595_STCP	IMX_GPIO_NR(1, 3)
#define HC595_SHCP	IMX_GPIO_NR(1, 2)
#define HC595_MR		IMX_GPIO_NR(1, 1)

#define HC595_DS1		IMX_GPIO_NR(4, 16)
#define HC595_OE1		IMX_GPIO_NR(3, 0)
#define HC595_STCP1	IMX_GPIO_NR(3, 1)
#define HC595_SHCP1	IMX_GPIO_NR(3, 2)
#define HC595_MR1		IMX_GPIO_NR(3, 3)

#define HC595_MAJOR	232

static int hc595_major = HC595_MAJOR;

struct cdev hc595_cdev;

static void hc595_setup(struct cdev *dev, int index);

static void hc595_config(void)
{
	if(0 != gpio_request(HC595_OE, "hc595_oe"))
		printk("hc595_drv: couldn't get hc595_oe gpio\n");
	else
		gpio_direction_output(HC595_OE, 0);
	
		
	if(0 != gpio_request(HC595_SHCP, "hc595_shcp"))
		printk("hc595_drv: couldn't get hc595_shcp gpio\n");
	else
		gpio_direction_output(HC595_SHCP, 0);
		
	if(0 != gpio_request(HC595_STCP, "hc595_stcp"))
		printk("hc595_drv: couldn't get hc595_stcp gpio\n");
	else
		gpio_direction_output(HC595_STCP, 0);
	
		
	if(0 != gpio_request(HC595_DS, "hc595_ds"))
		printk("hc595_drv: couldn't get hc595_ds gpio\n");
	else
		gpio_direction_output(HC595_DS, 0);
		
	
	if(0 != gpio_request(HC595_OE1, "hc595_oe1"))
		printk("hc595_drv: couldn't get hc595_oe1 gpio\n");
	else
		gpio_direction_output(HC595_OE1, 0);
	
		
	if(0 != gpio_request(HC595_SHCP1, "hc595_shcp1"))
		printk("hc595_drv: couldn't get hc595_shcp1 gpio\n");
	else
		gpio_direction_output(HC595_SHCP1, 0);
		
	if(0 != gpio_request(HC595_STCP1, "hc595_stcp1"))
		printk("hc595_drv: couldn't get hc595_stcp1 gpio\n");
	else
		gpio_direction_output(HC595_STCP1, 0);
	
		
	if(0 != gpio_request(HC595_DS1, "hc595_ds1"))
		printk("hc595_drv: couldn't get hc595_ds1 gpio\n");
	else
		gpio_direction_output(HC595_DS1, 0);
}

static int hc595_open(struct inode *inode, struct file *filp)
{
	//printk("hc595_open\n");
	filp->private_data = &hc595_cdev;
	return 0;
}

static ssize_t hc595_write(struct file *filp, const char __user *buf, size_t size, loff_t *ppos)
{
	int i, ret;
	unsigned char hc595_buf[6];
	
	memset(hc595_buf, 0, 6);
	ret = copy_from_user(hc595_buf, buf, size);
	//for(i = 0; i < size; i++)
	//	hc595_buf[i] = temp[5 - i];
//	printk("hc595_write %x %x %x %x %x %x\n", hc595_buf[0], hc595_buf[1], hc595_buf[2], hc595_buf[3], hc595_buf[4], hc595_buf[5]);
	 for(i = 0;i<6 * 8;i++)
   {  
   		gpio_direction_output(HC595_SHCP, 0);
   		gpio_direction_output(HC595_SHCP1, 0);
   		if(((hc595_buf[i/8] << (i%8)) & 0x80) == 0)
   		{
   			gpio_direction_output(HC595_DS, 0);
   			gpio_direction_output(HC595_DS1, 1);
   		}
   		else
   		{
   			gpio_direction_output(HC595_DS, 1);
   			gpio_direction_output(HC595_DS1, 0);
   		}
   		
   		gpio_direction_output(HC595_SHCP, 1);
   		gpio_direction_output(HC595_SHCP1, 1);
   }  
   gpio_direction_output(HC595_STCP, 0);
   gpio_direction_output(HC595_STCP, 1);
   gpio_direction_output(HC595_STCP1, 0);
   gpio_direction_output(HC595_STCP1, 1);
  

  //printk("hc165_drv: %02x %02x %02x %02x %02x\n", hc165_buf[0], hc165_buf[1], hc165_buf[2], hc165_buf[3], hc165_buf[4]) ;
	return size;
}

static int __init hc595_init(void)
{
	int ret;
	dev_t devno = MKDEV(hc595_major, 0);
	
	printk("hc595 init, devno %d\n", devno);
	
	if(hc595_major)
		ret = register_chrdev_region(devno, 1, "hc595");
	else
	{
		ret = alloc_chrdev_region(&devno, 0, 1, "hc595");
		hc595_major = MAJOR(devno);
	}
	
	if(ret < 0)
	{
		unregister_chrdev_region(devno, 1);
		return ret;
	}
		
	hc595_setup(&hc595_cdev, 0);
	hc595_config();
	
	return 0;
}

static const struct file_operations hc595_fops = {
		.owner = THIS_MODULE,
		.write = hc595_write,
		.open = hc595_open,
	//	.release = hc165_release,
		};

static void hc595_setup(struct cdev *dev, int index)
{
	int err, devno = MKDEV(hc595_major, index);
	
	cdev_init(dev, &hc595_fops);
	dev->owner = THIS_MODULE;
	err = cdev_add(dev, devno, 1);
	
	if(err)
		printk("error %d adding hc595%d\n", err, index);
		
}

static void __exit hc595_exit(void)
{
	printk("hc595 exit\n");
	cdev_del(&hc595_cdev);
	gpio_free(HC595_SHCP);
	gpio_free(HC595_STCP);
	gpio_free(HC595_OE);
	gpio_free(HC595_DS);
	gpio_free(HC595_SHCP1);
	gpio_free(HC595_STCP1);
	gpio_free(HC595_OE1);
	gpio_free(HC595_DS1);
	unregister_chrdev_region(MKDEV(hc595_major, 0), 1);
	
}

module_init(hc595_init);
module_exit(hc595_exit);

MODULE_AUTHOR("Artest");
MODULE_LICENSE("GPL v2");