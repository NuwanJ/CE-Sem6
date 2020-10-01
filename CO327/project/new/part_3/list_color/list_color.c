#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/types.h>
#include<linux/slab.h>

struct color {
	int red;
	int blue;
	int green;
	struct list_head list;
};

static LIST_HEAD(color_list);

int simple_init(void){

	struct color *c;
	struct color *ptr;
	int i;

	for(i=0;i<4;i++){
		c = kmalloc(sizeof(*c), GFP_KERNEL);

		c->red = 50;
		c->blue = 60;
		c->green = 70;

		INIT_LIST_HEAD(&c->list);
		list_add_tail(&c->list, &color_list);
	}

	printk(KERN_INFO "Inserting colors");
	printk(KERN_INFO "  Red\tGreen\tBlue");

	list_for_each_entry(ptr, &color_list, list) {
		printk(KERN_INFO "+ %d\t%d\t%d\n", ptr->red, ptr->green,ptr->blue);
	}

	return 0;
}

void simple_exit(void){
	struct color *ptr,*next;
	printk(KERN_INFO "Removing colors");
	printk(KERN_INFO "  Red\tGreen\tBlue");

	list_for_each_entry_safe(ptr,next, &color_list, list) {
		printk(KERN_INFO "- %d\t%d\t%d\n", ptr->red, ptr->green,ptr->blue);
		list_del(&ptr->list);
		kfree(ptr);
	}
}

/* Macros for registering module entry and exit points. */
module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Color Module");
MODULE_AUTHOR("SGG");
