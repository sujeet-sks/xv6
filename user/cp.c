#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"

int main(int argc, char *argv[]){
    
    if(argc != 3){
        printf("Invalid Number of arguments!\n");
        exit(1);
    }
    int fd_source = open(argv[1], O_RDONLY);
    if(fd_source < 0){
        printf("unable to open source file!\n");
        exit(1);
    }
    int fd_dest = open(argv[2], O_WRONLY | O_CREATE);
    
    if(fd_dest < 0){
        printf("unable to open destination file\n");
        close(fd_source);
        exit(1);
    }
    char buf[1]; 
    while(read(fd_source, buf, 1) > 0){
        int w = write(fd_dest, buf, 1);
        if(w < 0){
            printf("NOT able to write in destination file!\n");
            close(fd_source);
            close(fd_dest);
            exit(1);
        }
    }
    close(fd_source);
    close(fd_dest);
    printf("File copied successfully!\n");

    exit(0);
}