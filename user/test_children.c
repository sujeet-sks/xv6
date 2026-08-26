#include "kernel/fcntl.h"
#include "kernel/types.h"
#include "user/user.h"

int
main()
{

  printf("[parent] process with pid: %d \n", getpid());
  printf("Initial child count of %d = %d \n", getpid(), get_child_count());
  int c_pid[2];
  for (int i = 0; i < 2; i++) {
    c_pid[i] = fork();
    if (c_pid[i] < 0) {
      printf("Failed to fork child process!\n");
      exit(1);
    }
    if(c_pid[i] > 0){
        //inside parent process
        printf("child count of pid: %d after forking %d is %d\n",getpid(), i+1, get_child_count());
    }
    else{
        //inside child process
        if(fork() < 0 ){
            // creating one-one child of each child process
            printf("failed to create child process.\n");
        }
        exit(10);
    }
  }

  printf("child count of pid %d is %d\n", c_pid[0], get_process_child_count(c_pid[0]));
  printf("child count of pid %d is %d\n", c_pid[1], get_process_child_count(c_pid[1]));

  for(int i=0 ; i<2; i++){
    wait(0);
    printf("child reaped, new child count of pid: %d is %d\n",getpid(), get_child_count());
  }

    exit(0);
}