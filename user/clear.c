#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"

int main(){

    printf("\033[H\033[J");
    printf("| blank |\n");
    exit(1);
}