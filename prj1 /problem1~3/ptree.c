#include <linux/module.h>

#include <linux/kernel.h>

#include <linux/init.h>

#include <linux/sched.h>

#include <linux/unistd.h>

#include <linux/init.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/vmalloc.h>
#include <asm/uaccess.h>


#define MAXN 100
struct stack{
	struct task_struct *data[MAXN];
	int head;
}st;

int st_size(void){return st.head;}
bool st_empty(void){return st.head == 0;}
bool st_full(void){return st.head == MAXN;}

struct task_struct *st_pop(void){
	if(st_empty())return NULL;
	st.head -= 1;
	return st.data[st.head];
}
bool st_push(struct task_struct *t){
	if(st_full()) return false;
	st.data[st.head++]=t;
	return true;
}

struct task_struct *tsk,*p;
struct list_head *list,*list2;






MODULE_LICENSE("Dual BSD/GPL");

#define __NR_ptree 356








/*struct prinfo {
pid_t parent_pid;
pid_t pid;
pid_t first_child_pid; 
pid_t next_sibling_pid; 
long state;
long uid;
char comm[64];
};*/



static int (*oldcall)(void);

 void sys_ptree()

  
   
{   

while(!st_empty())
{
    tsk = st_pop();
    if((&tsk->children)->next!=(&tsk->children))
        printk(KERN_INFO "%s, %d, %d, %d\n", tsk->comm,tsk->state, tsk->real_parent->pid, tsk->pid);

    list_for_each_prev(list,&tsk->children){ 
	p = list_entry(list,struct task_struct, sibling);
	st_push(p);
    }
    list_for_each(list2,&tsk->children){
    
        p = list_entry(list2,struct task_struct, sibling);
         
        printk(KERN_INFO "	%s, %d, %d, %d\n",p->comm,p->state,p->real_parent->pid,  p->pid);
    }
}

    
}


    






/*int ptree(struct prinfo *buf, int *nr);*/



static int addsyscall_init(void ){



long *syscall=(long*) 0xc000d8c4;

oldcall=(int(*)(void)) (syscall[ __NR_ptree]);

syscall[ __NR_ptree]=(unsigned long)sys_ptree;

printk(KERN_INFO "module load!\n");



return 0;

}



static void addsyscall_exit(void ){





long *syscall=(long*) 0xc000d8c4;

syscall[ __NR_ptree]=(unsigned long) oldcall;

printk(KERN_INFO "module exit!\n");

}












module_init(addsyscall_init);

module_exit(addsyscall_exit);




