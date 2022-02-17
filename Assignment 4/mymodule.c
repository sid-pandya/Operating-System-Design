
#undef __KERNEL__
#define __KERNEL__

#undef MODULE
#define MODULE

#include <linux/module.h>
#include <linux/kernel.h>	
#include <linux/init.h>		

static int __init mymodule_init(void)
{
    printk(KERN_INFO "LOADING module, which was written by sid\n");
    return 0;	
}

static void __exit mymodule_cleanup(void)
{
    printk(KERN_INFO "UNLOADING module, which was written by sid\n");
}

module_init(mymodule_init);
module_exit(mymodule_cleanup);

/*
Output:-
sid@sid:~/assignment4$ sudo insmod mymodule.ko
sid@sid:~/assignment4$ dmesg | grep "was writtern by sid"
sid@sid:~/assignment4$ dmesg | grep "was written by sid"
[ 1287.278024] LOADING module, which was written by sid
sid@sid:~/assignment4$ sudo lsmod | grep "mymodule"
mymodule               16384  0
sid@sid:~/assignment4$ sudo rmmod mymodule
sid@sid:~/assignment4$ dmesg | grep "was written by sid"
[ 1182.435026] LOADING module, which was written by sid
[ 1240.545109] UNLOADING module, which was written by sid

*/
