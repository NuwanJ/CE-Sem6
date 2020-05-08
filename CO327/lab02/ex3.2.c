#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "sys/wait.h"

#define CAT_TO_GREP_READ_END 0
#define CAT_TO_GREP_WRITE_END 1
#define GREP_TO_CUT_READ_END 2
#define GREP_TO_CUT_WRITE_END 3


#define INPUTFILE "fixtures"

/**
* Executes the command "cat fixtures | grep <search_term> | cut -b 1-9".
*/

void die(const char*);

int main(int argc, char **argv)
{
    int status;
    int i;

    // arguments for commands
    char *cat_args[] = {"cat", INPUTFILE, NULL};
    char *grep_args[] =  {"grep", "-i", argv[1], NULL};
    char *cut_args[] =  {"cut", "-b", "1-9", NULL};

    int out = open("out", O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
    int in = open(INPUTFILE, O_RDONLY);

    // make 2 pipes (cat to grep and grep to cut); each has 2 fds

    int pipes[4];
    // sets up 1st pipe
    if(pipe(pipes) == -1) die("pipe()");

    // sets up 2nd pipe
    if(pipe(&pipes[2]) == -1) die("pipe()");

    for(int i=0;i<4;i++){
        //printf("%d\n", pipes[i]);
    }

    // we now have 4 fds:
    // pipes[0] = read end of cat->grep pipe (read by grep)
    // pipes[1] = write end of cat->grep pipe (written by cat)
    // pipes[2] = read end of grep->cut pipe (read by cut)
    // pipes[3] = write end of grep->cut pipe (written by grep)

    // fork the first child (to execute cat)

    if (fork() == 0){
        // First child gets here, which executes 'cat' command

        // replace cat's stdout with write part of 1st pipe
        if(dup2(pipes[CAT_TO_GREP_WRITE_END], STDOUT_FILENO) == -1) die("dup()");

        // close all pipes (very important!); end we're using was safely copied
        for(int i=0;i<4;i++){
            //printf("closing %d\n", pipes[i]);
            close(pipes[i]);
        }

        // Execute the cat command
        if(execvp("cat", cat_args) == -1) die("execvp(cat)");
    }
    else{
        // Parent comes here

        if (fork() == 0){
            // Second child comes here, which executes 'grep' command

            // replace grep's stdin with read end of 1st pipe
            if(dup2(pipes[CAT_TO_GREP_READ_END], STDIN_FILENO) == -1) die("dup(grep's stdin with read end of 1st pipe)");

            // replace grep's stdout with write end of 2nd pipe
            if(dup2(pipes[GREP_TO_CUT_WRITE_END], STDOUT_FILENO) == -1) die("dup(grep's stdout with write end of 2nd pipe)");

            // close all ends of pipes
            for(int i=0;i<4;i++){
                close(pipes[i]);
            }

            // execute grep command
            if(execvp("grep", grep_args) == -1) die("execvp(grep)");

        } else{
            // Second Child as Parent
            
            if (fork() == 0){
                // Third child comes here

                if(dup2(pipes[GREP_TO_CUT_READ_END], STDIN_FILENO) == -1) die("dup(cut's stdin with input read of 2nd pipe)");

                // close all ends of pipes
                for(int i=0;i<4;i++){
                    close(pipes[i]);
                }

                // execute cut command and out to STDOUT
                if(execvp("cut", cut_args) == -1) die("execvp(cut)");
                printf("Error\n");
            }
        }
    }

    // only the parent gets here and waits for 3 children to finish
    // It's a good idea to close all your pipes (the parent needs none!)
    // before waiting for your children!

    for(int i=0;i<4;i++){
        close(pipes[i]);
    }
    wait(NULL);
}

void die(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}
