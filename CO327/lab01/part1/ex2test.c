
#include "stdio.h"
#include "sys/types.h"
#include "unistd.h"


int main(int argc, char const *argv[]) {

    pid_t pid;

    pid = fork();

    if (pid<0) {
        perror("Fork Erorr !");
        return (1);

    }else if(pid==0){
        //puts("This is the child process");
        printf("This is a child process %d of %d\n", getpid(), getppid());
        while(1){
            continue;
        }
    }else{
        puts("This is the parent process");
        printf("child PID=%d\n", (int)pid);
        while(1){
            continue;
        }
    }
    return 0;
}
