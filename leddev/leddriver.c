#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/ide.h>
#include <linux/init.h>
#include <linux/module.h>

#define CHARDEV_MAJOR 200
#define CHARDEV_NAME "mychardev"

static char read_buff[100];
static char write_buff[100];
static char kernel_data[]={"[kernel info] this a chardev."};

static int chardev_open(struct inode *inode,struct file *filep)
{
	printk("you has open this chardev.\n");
	return 0;
}

static ssize_t chardev_read(struct file *filep,char __user *buf,size_t cnt,loff_t *offt)
{
	int ret=0;
	memset(read_buff,0,sizeof(read_buff));
	memcpy(read_buff,kernel_data,sizeof(kernel_data));
	ret=copy_to_user(buf,read_buff,cnt);
	if(ret<0){
		printk("copy to user error.\n");
	}else{
		printk("copy to user:%s.\n",read_buff);
	}
	return ret;
}
static ssize_t chardev_write(struct file *filep,const char __user *buf,size_t cnt,loff_t *offt)
{
	int ret=0;
	memset(write_buff,0,sizeof(write_buff));
	ret=copy_from_user(write_buff,buf,cnt);
	if(ret<0){
		printk("copy from user error.\n");
	}else{
		printk("copy to user:%s.\n",write_buff);
	}
	return ret;
}

static int chardev_release(struct inode *inode,struct file *filep)
{
	printk("you has close the chardev.\n");
	return 0;
}

static struct file_operations chardev_fops={
	.owner=THIS_MODULE,
	.open=chardev_open,
	.read=chardev_read,
	.write=chardev_write,
	.release=chardev_release,
};

static int __init chardev_init(void)
{
	int ret=0;
	ret=register_chrdev(CHARDEV_MAJOR,CHARDEV_NAME,&chardev_fops);
	if(ret<0){
		printk("register char dev error.\n");
		return ret;
	}
	printk("char_dev inited.\n");
	return ret;
}

static int __exit chardev_exit(void)
{
	unregister_chrdev(CHARDEV_MAJOR,CHARDEV_NAME);
	printk("char_dev exited.\n");
	return 0;
}

module_init(chardev_init);
module_exit(chardev_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("wangli");



	