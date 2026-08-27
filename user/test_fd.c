#include "kernel/fcntl.h"
#include "kernel/types.h"
#include "user/user.h"


int main(){

    int fd = open("dummy.txt", O_RDWR);
    printf("[parent] fd = %d  inode = %d  offset = %d \n", fd, get_inode_num(fd), get_read_offset(fd));
    printf("[parent] forking a child. \n");
    int pid = fork();
    if(pid < 0){
        printf("unable to create child.\n");
        exit(1);
    }
    if(pid == 0){
        // inside child
        printf("[child] fd = %d  inode = %d  offset = %d \n", fd, get_inode_num(fd), get_read_offset(fd));
        printf("reading 5 Byte from fd = %d \n", fd);
        char *c;
        read(fd, &c, 5);
        printf("[child] fd = %d  inode = %d  offset = %d \n", fd, get_inode_num(fd), get_read_offset(fd));
        exit(0);
    }
    else{
        //inside parent
        wait(0);
        printf("[parent] reaping child... \n");
        printf("[parent] fd = %d  inode = %d  offset = %d \n", fd, get_inode_num(fd), get_read_offset(fd));
    }

    exit(0);
}