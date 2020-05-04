
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "string.h"

#include "sys/types.h"
#include "sys/wait.h"

int replaceChar(char *str, char orig, char rep) {
    char *ix = str;
    int n = 0;
    while((ix = strchr(ix, orig)) != NULL) {
        *ix++ = rep;
        n++;
    }
    return n;
}

char **getInputArgs(char *input) {
    char **command = malloc(8 * sizeof(char *));
    char *separator = " ";
    char *parsed;
    int index = 0;

    parsed = strtok(input, separator);
    while (parsed != NULL) {
        command[index] = parsed;
        index++;
        parsed = strtok(NULL, separator);
    }
    command[index] = NULL;
    return command;
}

int main(int argc, char const *argv[]) {

    char **myArgs;
    char *input;
    pid_t pid;
    char buf[256];

    while (1) {
        printf("\nSHELL >> ");

        fgets(buf, 1023, stdin);        // read a line
        replaceChar(buf, '\n', '\0');   // Replace new line char with line end
        //printf("command: %s \n", buf);  // Print the input command

        if(strlen(buf)>1){
            input = malloc(sizeof(char)*(strlen(buf)));
            strcpy(input, buf);

            myArgs = getInputArgs(buf);

            if(strcmp(myArgs[0], "exit")==0){
                exit(0);        // Exit from the shell
            }

            pid = fork();

            if (pid <0) {
                perror("Fork failed");
                exit(1);

            } else if (pid == 0) {
                // Child
                execvp(myArgs[0], myArgs);
                printf("Error occurred\n");

            } else {
                // Parent
                wait(NULL);
            }

            free(input);
            free(myArgs);
        }
    }

    return 0;
}
