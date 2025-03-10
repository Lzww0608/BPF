#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>

pid_t pid = 0;
module_param(pid, int, S_IRUSR);

// sudo insmod kernel_module.ko
static int __init kernel_module_init(void) {
#if 0
    struct pid *spid;

    struct task_struct *task;

    spid = find_get_pid(pid);

    task = get_pid_task(spid, PIDTYPE_PID);

    printk(KERN_INFO "kernel module init: %d, %s\n", pid, task->comm);

#else 
    struct task_struct *task;

    for_each_process(task) {
        printk(KERN_INFO "kernel module init: %d, %s\n", task->pid, task->comm);
    }
#endif

    return 0;

}

// sudo rmmod kernel_module
static void __exit kernel_module_exit(void) {
    printk(KERN_INFO "kernel module exit\n");
}

module_init(kernel_module_init);
module_exit(kernel_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Lzww");
MODULE_DESCRIPTION("A simple kernel module");