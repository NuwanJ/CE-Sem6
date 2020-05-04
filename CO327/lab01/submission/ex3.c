
#include "stdio.h"
#include "stdlib.h"
#include "sys/types.h"
#include "unistd.h"
#include "sys/wait.h"

int main(int argc, char const *argv[]) {

    pid_t pid[4];
    printf("i=0\ti=1\ti=2\n");

    for (int i = 0; i < 3; i++) {
        pid_t p = fork();

        //printf("%d\t%d\t%d \t", getppid(), getpid(),p);

        for(int j=0;j<i;j++){
            printf("\t");
        }

        printf("Hello\n");
        if(p>0) wait(NULL);
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
