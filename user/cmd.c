#include "kernel/fcntl.h"
#include "kernel/types.h"
#include "user/user.h"


int main(int argc, char *argv[]){

    int pid = fork();
    if(pid < 0){
        printf("failed to create child process!");
        exit(0);
    }
    
    // modifying argv for exec
    for(int i=0; i<argc; i++){
        if(i == argc-1){
            argv[i] = 0;
        }
        else{
            argv[i] = argv[i+1];
        }
    }
    if(pid == 0){
        //inside child
        if(exec(argv[0],argv) == -1){
            //incase exec failed
            printf("failed to execute %s command\n", argv[0]);
            exit(0);
        }
    }
    else{
        //indide parent
        int status;
        wait(&status);
    }
    exit(1);
}