#include <linux/init.h>
#include <linux/module.h>
#include <linux/workqueue.h>
#include <linux/kmod.h>
 
 
static void delayed_ls(struct work_struct *work);
static DECLARE_DELAYED_WORK(list_dir, delayed_ls);
 
static void delayed_ls(struct work_struct *work)
{
        char *cmd = "/bin/bash";
        char *argv[] = {cmd, "-c", "/bin/ls / >> /tmp/kerneltest-delayed.txt", NULL};
        char *envp[] = {"HOME=/", "TERM=linux", "PATH=/sbin:/bin:/usr/sbin:/usr/bin", NULL};
        int ret = call_usermodehelper(cmd, argv, envp, UMH_WAIT_PROC);
        printk("Returned error is %d\n", ret);
        printk("%s called!\n", __FUNCTION__);
}

static void immediate_ls(void)
{
        char *cmd = "/bin/bash";
        char *argv[] = {cmd, "-c", "/bin/ls /dev >> /tmp/kerneltest-immediate.txt", NULL};
        char *envp[] = {"HOME=/", "TERM=linux", "PATH=/sbin:/bin:/usr/sbin:/usr/bin", NULL};
        int ret = call_usermodehelper(cmd, argv, envp, UMH_WAIT_PROC);
        printk("Returned error is %d\n", ret);
        printk("%s called!\n", __FUNCTION__);
	
}
 
static int __init onload(void)
{
        schedule_delayed_work(&list_dir, msecs_to_jiffies(2000));
	immediate_ls();
        return 0;
}
 
static void __exit onunload(void)
{
        printk("So long buddy\n");
}
 
module_init(onload);
module_exit(onunload);
MODULE_AUTHOR("Liam Ryan <liamryandev@gmail.com>");
MODULE_LICENSE("GPL");
