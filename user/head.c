#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"


int main(int argc, char *argv[]){
    //
    if(argc!=3){
        printf("Invalid number of argumnets\n");
        exit(0);
    }
    int total_lines = atoi(argv[2]); // to convert char * to int
    if(total_lines <= 0){
        printf("Please type number of lines to read greater than 0\n");
        exit(0);
    }
    int fd = open(argv[1],O_RDONLY);
    int line = 0;
    char c;
    while(read(fd, &c, 1)>0){
        //reading char by char
        printf("%c", c);
        if(c == '\n'){
            line++;
        }
        if(line == total_lines)break;
    }
    if(line != total_lines){
        printf("Not able to read desired number of lines!\n");
    }
    close(fd);
    exit(1);
}