#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#include <stdio.h>
#include <string.h>

#define MAX_SIZE 1024

void die(const char *msg);

int main(){

    char* input = "/tmp/input";
    char* output = "/tmp/output";
    char buff[MAX_SIZE];
    char buff2[MAX_SIZE];

    int inputFd, outputFd;

    mkfifo(input, 0666);
    mkfifo(output, 0666);

    inputFd = open(input, O_WRONLY); // Write into input FIFO
    outputFd = open(output, O_RDONLY); // Read from the output FIFO

    while(1){
        fgets(buff, MAX_SIZE, stdin);         // read a line from stdin
        buff[strlen(buff)-1] = '\0';
        printf("stdin: %s\n", buff);

        if(strlen(buff)>0){
            // Write into input FIFO
            if(write(inputFd, buff, strlen(buff))<0){
                die("write error");
            }

            // Read from the output FIFO
            int len = read(outputFd, buff2, MAX_SIZE);
            buff2[len] = '\0';
            printf("FIFO: %s\n\n", buff2);
        }
    }

    // Unlink FIFO files
    unlink(input);
    unlink(output);

    return 0;
}
void die(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}
