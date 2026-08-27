#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main() {
    printf("square of 2 is %d\n", sqNumber(2));
    printf("square of 5 is %d\n", sqNumber(5));
    exit(0);
}
