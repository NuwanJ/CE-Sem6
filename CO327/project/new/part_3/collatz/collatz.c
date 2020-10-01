#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/types.h> 
#include<linux/slab.h>
#include<linux/moduleparam.h>
#include <linux/delay.h>

static int start = 25;

module_param(start, int, 0);

struct collatz {
	int data; 
	struct list_head list;
};

static LIST_HEAD(collatz_list);
/* This function is called when the module is loaded. */

int simple_init(void){
	int n = start;
	struct collatz *ptr;
	struct collatz *l;
	
	printk(KERN_INFO "Generating Collatz\n");
	while( n != 1)
	{
		l = kmalloc(sizeof(*l), GFP_KERNEL);
		l->data = n;
		INIT_LIST_HEAD(&l->list);
		list_add_tail(&l->list, &collatz_list);
		if(n & 1){
			n = 3*n + 1;
		}
		else{
			n = n/2;
		}	
	}
	l = kmalloc(sizeof(*l), GFP_KERNEL);
	l->data = 1;
	list_add_tail(&l->list, &collatz_list);
	mdelay(100);
	printk(KERN_INFO "Traversing Collatz\n");
	list_for_each_entry(ptr, &collatz_list, list) {
		printk(KERN_INFO "%d\n", ptr->data);
	}
	

	return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void)
{
	struct collatz *ptr,*next;
	printk(KERN_INFO "Removing Collatz∖n");
	
	list_for_each_entry_safe(ptr,next, &collatz_list, list) {
		printk(KERN_INFO "%d\n", ptr->data);
		list_del(&ptr->list);
		kfree(ptr);
	}
}

/* Macros for registering module entry and exit points. */
module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");
