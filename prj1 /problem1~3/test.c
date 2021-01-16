#include<linux/unistd.h>
#include<sys/syscall.h>
#include <linux/sched.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>



#include<sys/types.h>
#include<sys/wait.h>


//struct task_struct init_task;

int main(){



pid_t pid;
pid=fork();

if (pid<0){
fprintf(stderr, "Fork Failed");
return 1;
}
else if (pid==0){
printf("518030990025_Child pid:%d\n", pid);

syscall(356);
//execlp("～/test/test1.c", NULL);


}
else{
wait(NULL);
printf("518030990025_Parent pid:%d\n", pid);
}

return 0;
}
//printf("%s,%d,%ld,%d,%d,%d,%d\n", p.comm, p.pid, p.state,p.parent_pid, p.first_child_pid, p.next_sibling_pid, p.uid);
