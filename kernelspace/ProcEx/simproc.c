/*
 * $Id: hello2.c,v 1.8 2001/07/18 22:28:18 rubini Exp $
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>	/* printk() */
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
static ssize_t myproc_write(struct file *file,const char __user *buf,size_t count,loff_t *ppos)
{
	printk("val=%s\n",buf);
	return count;
}

static ssize_t myproc_read(struct file *file, char __user *buf,size_t count,loff_t *ppos)
{
   if(*ppos > 0)
	   return 0;
   copy_to_user(buf , "test proc" , 9);
   *ppos=9;
   return 9;

}
static struct file_operations proc_fops =
{
	.read = myproc_read,
	.write = myproc_write,
};


static int hello_init (void)
{
  struct proc_dir_entry *pr;
  pr=proc_create("mytest",0660,NULL,&proc_fops);

  printk (KERN_INFO "Hello loaded sucessfuly.\n");

  
  return 0;

}


static void
hello_cleanup (void)
{

  printk (KERN_INFO "hello unloaded succefully.\n");

}


module_init (hello_init);
module_exit (hello_cleanup);
MODULE_LICENSE("Dual BSD/GPL");
