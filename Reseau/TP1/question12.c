#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>

int main(int argc, char* argvi[])
{
    while (2+2 == 4){
        pid_t pid = getpid();
        printf("pid %d is running on the CPU number %d\n", pid, sched_getcpu());
    }    
    return 0;
}
