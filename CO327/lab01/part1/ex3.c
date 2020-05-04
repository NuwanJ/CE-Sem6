
#include "stdio.h"
#include "stdlib.h"
#include "sys/types.h"
#include "unistd.h"
#include "sys/wait.h"

int main(int argc, char const *argv[]) {

    pid_t pid[4];
    //printf("\n\n-- %d --\n\n", getpid());
    printf("i=0\ti=1\ti=2\n");


    for (int i = 0; i < 3; i++) {
        pid_t p = fork();

        for(int j=0;j<i;j++){
            printf("\t");
        }

        if(p>0) wait(NULL);
        printf("Hello\n");
    }

    return 0;
}

/*
Output:

i=0	i=1	i=2
Hello
	Hello
		Hello
		Hello
	Hello
		Hello
		Hello
Hello
	Hello
		Hello
		Hello
	Hello
		Hello
		Hello


*/
