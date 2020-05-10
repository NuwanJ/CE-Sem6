/*

a.
write(STDOUT_FILENO, &buff, count)
   This will write the contents on char buffer named 'buff' (from its index 0 to the index 'count-1') to the standard output (default; to the terminal)

b.
Theoretically it is possible to read and  write from both ends.
But if both parent and child write to the pipes at same time, the data can be corrupted. (No concurrency control in pipes)
So it is recommended to use two pipes for bi-directional communication.

c.
unnamed pipes are implemented only to communicate between parent and child processes.
The implement is not supported to pass the read or write descriptors to outside process except child of the current process.

d. [Find the below code]

*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <unistd.h>

#define READ_END 0
#define WRITE_END 1

const char banner [] = "hello there\n";

int main()
{
    int pipe_parent2child[2];
    int pipe_child2parent[2];
    pid_t pid;

    // Create a pipe to send data from the parent to child
    if(pipe(pipe_parent2child)){
        perror("Pipe creation");
        return -1;
    }
    // Create a pipe to send data from child to parent
    if(pipe(pipe_child2parent)){
        perror("Pipe creation");
        return -1;
    }

    pid = fork();
    if(pid < 0){
        perror("Fork");
        return -1;
    }

    if(pid > 0){
        /* parent : send chars read fron the stdin to child */
        close(pipe_parent2child[READ_END]);
        close(pipe_child2parent[WRITE_END]);

        char buff[255];
        char buff2[255];
        while(1){
            fgets(buff, 255, stdin);        // read a line
            buff[strlen(buff)-1] = '\0';   // Replace new line char with line end

            printf("Parent writes '%s' to the pipe.\n", buff);
            write(pipe_parent2child[WRITE_END], buff, strlen(buff));
            sleep(2);

            read(pipe_child2parent[READ_END], buff2, 255);
            printf("Child say, '%s'\n\n", buff2);

        }
        close(pipe_parent2child[WRITE_END]);
        close(pipe_child2parent[READ_END]);

    }

    if(pid == 0){
        /* child : reads input pipe and write the capitalized chars to output pipe*/
        char buffC[128];
        int count;
        close(pipe_parent2child[WRITE_END]);
        close(pipe_child2parent[READ_END]);

        while((count = read(pipe_parent2child[READ_END], buffC, 128)) > 0) {
            for(int i=0;i<strlen(buffC);i++){
                // Capitalize the simple alphabet letters
                if(buffC[i]>=97 && buffC[i]<=122)buffC[i] = toupper(buffC[i]);
            }
            write(pipe_child2parent[WRITE_END], buffC, strlen(buffC));
            sleep(1);
        }
        close(pipe_parent2child[READ_END]);
        close(pipe_child2parent[WRITE_END]);
    }
    return 0;
}
