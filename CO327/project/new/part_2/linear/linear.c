#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>


/* This function is called when the module is loaded. */

int simple_init(void){
	struct task_struct *task;
	printk(KERN_INFO "PID\tSTATE\tCOMM");
	for_each_process(task){
		printk(KERN_INFO "%d\t%ld\t%s", task->pid,task->state,task->comm);	
	}
	return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void)
{
	printk(KERN_INFO "Removing Kernel Module∖n");
}

/* Macros for registering module entry and exit points. */
module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");
