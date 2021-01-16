
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/sched.h>
#include<linux/unistd.h>
#include<linux/slab.h>
#include <linux/uaccess.h>
#include <linux/list.h>	
#include <linux/mm.h>
#include <linux/mutex.h>

MODULE_LICENSE("Dual BSD/GPL");
#define __NR_set_mm_limit_call 383

static int (*oldcall)(void);


int initialized = 0;//ensure struct is initialized only ONCE
DEFINE_MUTEX(init_mutex);
struct MMLimits my_mm_limits[upperBound]; //declare global array my_mm_limits

void init_my_mm_limits() {
    int i;
    for (i=0; i<upperBound; i++){
	my_mm_limits[i].uid = -1;
	my_mm_limits[i].mm_max = -1;
    }
}


int set_mm_limit(uid_t uid, unsigned long mm_max){
	// ensure struct is initialized only ONCE
    	mutex_lock(&init_mutex);
    	if (!initialized) {
        	initialized = 1;
        	init_my_mm_limits();
    	}
    	mutex_unlock(&init_mutex);

	printk("enter system call\n");
	struct MMLimits* temp = my_mm_limits; //use another pointer to point to my_mm_limits array
    static int i=0;
    bool flag=1;//judge whether add a new item or not
    
    
    
    
    //check for existence
    for (j=0; j<i; j++){
        if (temp->uid==uid)  {
            temp->mm_max=mm_max;
            flag=0;
            break;
        }
        temp++;
    }
    
    if (flag){
        if (i<upperBound){
            temp->uid=uid;
            temp->mm_max=mm_max;
            ++i;
        }
        else return -1;//The array is full
        
    }
    for (j=0; j<upperBound; j++){
        if (temp->uid!=-1)
            printk("uid=%d, mm_max=%d\n", temp->uid, temp->mm_max);
        temp++;
    }
    
    return 0;

}



static int set_mm_limit_init(void) {
	long *syscall = (long *)0xc000d8c4;
	oldcall = (int (*)(void))(syscall[__NR_set_mm_limit_call]);
	syscall[__NR_set_mm_limit_call] = (unsigned long)set_mm_limit;
	printk(KERN_INFO "Module set_mm_limit has been loaded!\n");
	return 0;
}

static void set_mm_limit_exit(void) {
	long *syscall = (long *)0xc000d8c4;
	syscall[__NR_set_mm_limit_call] = (unsigned long)oldcall;
	printk(KERN_INFO "Module set_mm_limit has been removed!\n");
}

module_init(set_mm_limit_init);
module_exit(set_mm_limit_exit);
