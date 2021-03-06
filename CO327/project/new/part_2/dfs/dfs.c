#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>


void dfs(struct task_struct *task)
{
	struct task_struct *task_next;
	struct list_head *list;

	//printk(KERN_INFO "\n");

	list_for_each(list, &task->children) {
		task_next = list_entry(list, struct task_struct, sibling);
		printk(KERN_INFO "%d\t%ld\t%s", task_next->pid,task_next->state,task_next->comm);
		dfs(task_next);
	}
}

int simple_init(void){
	dfs(&init_task);
	return 0;
}

void simple_exit(void){
	printk(KERN_INFO "Removing Kernel Module, DFS∖n");
}

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("DFS Process List Module");
MODULE_AUTHOR("SGG");
