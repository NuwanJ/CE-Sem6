#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

int simple_init(void){
	struct task_struct *task;
	printk(KERN_INFO "PID\tState\tComm");

	for_each_process(task){
		printk(KERN_INFO "%d\t%ld\t%s", task->pid,task->state,task->comm);
	}
	return 0;
}

void simple_exit(void){
	printk(KERN_INFO "Removing Kernel Module∖n");
}

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Linear Process List Module");
MODULE_AUTHOR("SGG");
