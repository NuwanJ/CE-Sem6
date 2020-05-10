#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#include <stdlib.h>
#include <ctype.h>
#include "sys/types.h"
#include "sys/wait.h"

#define MAX_SIZE 1024
#define READ_END 0
#define WRITE_END 1

void die(const char *msg);

int main(int argc, char const *argv[]) {

    char* input = "/tmp/input";
    char* output = "/tmp/output";
    char *tr_args[] =  {"tr", "[a-z]]", "[A-Z]", NULL};

    int inputFd, outputFd;

    mkfifo(input, 0666);
    mkfifo(output, 0777);//0666);

    inputFd = open(input, O_RDONLY);
    outputFd = open(output, O_WRONLY);

    char buff[MAX_SIZE];
    pid_t pid;
    int len;

    while(1){   // For each input

        // Read from FIFO
        len=read(inputFd, buff, MAX_SIZE);
        if(len<=0) exit(0);

        buff[len] = '\0';
        printf("Read: %s\n", buff);

        // Create a pipe
        int pipe_ends[2];
        if(pipe(pipe_ends)<0) die("pipe_ends");

        pid = fork();

        if(pid < 0){
            // Failed to create a pipe
            die("Fork");

        }else if (pid>0){
            // Parent process

            // Close unsued pipe_ends
            close(pipe_ends[READ_END]);

            // Write into the pipe_ends
            write(pipe_ends[WRITE_END], buff, len);

            // Close the completed write end too
            close(pipe_ends[WRITE_END]);

        }else if(pid == 0){
            // Child process

            // Close unsued pipe_ends
            close(pipe_ends[WRITE_END]);

            //Change standard input and output with FIFO input and output
            if(dup2(pipe_ends[READ_END], STDIN_FILENO)==-1) die("input");
            if(dup2(outputFd, STDOUT_FILENO)==-1) die("output");

            // Close unsued ends
            close(pipe_ends[READ_END]);
            close(outputFd);

            if(execvp("tr", tr_args) == -1) die("execvp(tr)");
            printf("Error\n");

            exit(0);
        }
    }

    return 0;
}

void die(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}
