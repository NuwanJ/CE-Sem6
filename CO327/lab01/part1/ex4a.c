
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "string.h"
//#include "readline/readline.h"

#include "sys/types.h"
#include "sys/wait.h"

int main(int argc, char const *argv[]) {

    char path[64];
    char buf[256];
    char word[32];

    scanf("%99[^\n]%*1[\n]", buf);
    printf("\n%s\n--------------\n", buf);

    int count=0;
    char **myArgs = malloc(sizeof(char *)*16);
    char *pch;

    pch = strtok(buf," ,");
    sprintf(word, "%s",pch);
    char * cmd = malloc(sizeof(char)*strlen(word));
    strcpy(cmd, word);

    pch = strtok(buf," ,");
    while (pch != NULL){
        sprintf(word, "%s",pch);
        pch = strtok (NULL, " ,");
        myArgs[count] = malloc(sizeof(char)*strlen(word));
        strcpy(myArgs[count], word);
        printf("\t%s\n", myArgs[count]);
        count++;
    }

    for (int k=0;k<count;k++){
        printf("> %s\n", myArgs[k]);
    }
    myArgs[count] = NULL;

    sprintf(path, "/bin/%s", cmd);
    printf("%s %s %s\n", path, myArgs[0],myArgs[1]);
    execl(path, *(myArgs), NULL);
    printf("\n\nProgram has terminated\n");

    return 0;
}


/************************************

Exercise 1

1. 0 times, since execl doesn't return


*************************************/
