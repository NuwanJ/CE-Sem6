/*

How many times is the message “ Program ls has terminated ” printed?

0 times, since exec command not retuns unless it fails.

*/


#include "sys/types.h"
#include "sys/wait.h"
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

int main(int argc, char const *argv[]) {

    execl("/bin/ls", "-l", argv[1], NULL);
    puts("Program ls has terminated");

    return 0;
}
