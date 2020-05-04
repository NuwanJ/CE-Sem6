
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "sys/types.h"
#include "sys/wait.h"

int main(int argc, char const *argv[]) {

    execl("/bin/ls", "-l", argv[1], NULL);
    printf("\n\nProgram ls has terminated\n");

    return 0;
}
