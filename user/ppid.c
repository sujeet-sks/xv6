#include "kernel/fcntl.h"
#include "kernel/types.h"
#include "user/user.h"

int main(void){

    int parentId = getpid();
    printf("[parent] my pid is %d \n", parentId);
    printf("[parent] forking a child process\n");
    int pid = fork();
    if(pid < 0){
        printf("failed to create child process!\n");
        exit(1);
    }
    if(pid == 0){
        //inside child process
        printf("[child] my pid is %d \n", getpid());
        printf("[child] my parent is %d \n", getppid());
        exit(0);
    }
    else{
        wait(0);
    }
    exit(0);
}