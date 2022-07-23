
/**
* This LKM takes a PID as a parameter and prints information about all the processes
* and their children and thier parent with PID larger than the input PID
*
* Completion time: 8 hours
*
* @author (Mohammad Hamdan)
* @version (1.0)
*/







#include <linux/module.h>          
#include <linux/kernel.h>
#include <linux/sched.h>        
#include <linux/init.h>
#include <linux/sched/signal.h>
#include <linux/list.h>
#include <linux/moduleparam.h>
#include <linux/pid.h> 

static int inp_pid = 1;
module_param(inp_pid, int, 0644);


static int start_init(void)
{
       

        struct task_struct* task_list;
         struct task_struct* task_child;       
         struct list_head *list; 
            
       task_list = pid_task(find_vpid(inp_pid), PIDTYPE_PID);

        
        for_each_process(task_list) {
                printk("Process       PID       STATE       PRIO       ST_PRIO       NORM_PRIO\n");
                printk("%s       %d       %ld       %d       %d       %d\n", task_list->comm, task_list->pid, task_list->state, task_list->prio, task_list->static_prio, task_list->normal_prio);
                printk("PARENT\n");
                printk("%s       %d       %ld       %d       %d       %d\n", task_list->parent->comm, task_list->parent->pid,  task_list->parent->state,  task_list->parent->prio,  task_list->parent->static_prio,  task_list->parent->normal_prio);
                
                list_for_each(list, &task_list->children){

                task_child = list_entry(list, struct task_struct, sibling);
                printk("CHILD\n");
                printk("%s       %d       %ld       %d       %d       %d\n", task_child->comm,task_child->pid, task_child->state, task_child->prio, task_child->static_prio, task_child->normal_prio); 
                }
                printk("\n");
        }

        return 0;
}

static void end_exit(void)
{
        printk(KERN_INFO "== CLEANUP ]\n");
}


module_init(start_init);
module_exit(end_exit);

