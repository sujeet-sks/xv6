#include "kernel/fcntl.h"
#include "kernel/types.h"
#include "user/user.h"

int main(){

    printf("Syscall count for current process: \n");
    print_syscalls();
    printf("Syscall count for pid: %d \n", 3);
    print_process_syscalls(3);

    exit(0);
}