#include "kernel/fcntl.h"
#include "kernel/types.h"
#include "user/user.h"

int
main()
{

  int parentId = getpid();
  int child_pid[3];
  printf("[parent] pid : %d \n", parentId);
  printf("[parent] forking 3 children. \n");

  int cdc = nfork(3, child_pid);

  if (cdc == 0) {
    printf("[child] pid: %d, ppid: %d \n", getpid(), getppid());
  }

  exit(0);
}