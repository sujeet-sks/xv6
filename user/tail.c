#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"

int main(int argc, char *argv[]){

    if(argc != 3){
        printf("Invalid number of arguments\n");
        exit(0);
    }
    int read_lines = atoi(argv[2]);
    if(read_lines <= 0){
        printf("Please enter valid number of lines to read\n");
        exit(0);
    }
    int total_lines = 0;
    int fd = open(argv[1], O_RDONLY);
    char c;
    while((read(fd, &c, 1)) > 0){
        //getting total number of lines
        if(c == '\n'){
            total_lines++;
        }
    }
    // printf("total line are: %d\n", total_lines);
    int skip_lines = total_lines - read_lines;
    // if(total_lines <= skip_lines){

    // }
    // Moves the internal file read pointer back to offset 0 (the beginning)
    close(fd);
    fd = open(argv[1], O_RDONLY); // to move pointer back to start of file
    int current_line = 0;
    while((read(fd, &c, 1)) > 0){
        if(current_line >= skip_lines){
            printf("%c",c);
        }
        if(c == '\n'){
            current_line++;
        }
    }
    close(fd);

    exit(1);
}