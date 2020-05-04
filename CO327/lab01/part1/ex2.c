
#include "stdio.h"
#include "stdlib.h"
#include "sys/types.h"
#include "unistd.h"
#include "sys/wait.h"

int main(int argc, char const *argv[]) {

    pid_t pid[4];
    //printf("\n\n-- %d->%d --\n\n",getppid(), getpid());
    //printf("parent\tprocess\tchild\ti=0\ti=1\ti=2\n");

    for (int i = 0; i < 3; i++) {
        pid_t p = fork();

        printf("i=0\ti=1\ti=2\n");
        //printf("%d\t%d\t%d \t", getppid(), getpid(),p);

        for(int j=0;j<i;j++){
            printf("\t");
        }

        printf("Hello\n");
        //if(p>0) wait(NULL);
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


1. Parent always prints first.


2. Total 7 children spawn from the process 11602.

11602──> 11603──> 11604──> 11605
    │        └──> 11606
    ├──> 11607──> 11608
    └──> 11609

parent	process	child	i=0	    i=1	   i=2
10209	11602	11603 	Hello
11602	11603	0    	Hello
11602	11603	11604 		    Hello
11603	11604	0   		    Hello
11603	11604	11605 		    	   Hello
11604	11605	0    		 	       Hello
11602	11603	11606 		    	   Hello
11603	11606	0    			       Hello
10209	11602	11607 		    Hello
11602	11607	0    		    Hello
11602	11607	11608 			       Hello
11607	11608	0   			       Hello
10209	11602	11609 			       Hello
11602	11609	0    			       Hello

(Printed with wait option for best view)

*/
