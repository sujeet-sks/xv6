#include "kernel/fcntl.h"
#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]){
    if(argc != 2){
        printf("pass correct number of arguments.\n");
        printf("Also pass integer number whose square you want to compute.\n");
        exit(1);
    }
    int n = atoi(argv[1]);
    int sq = sqNumber(n);
    printf("Square of %d is %d \n", n, sq);

    exit(0);
}