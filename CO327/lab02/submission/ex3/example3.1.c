#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

/**
 * Executes the command "grep 'New Zealand' < fixtures > out".
 */

int main(int argc, char **argv)
{
        int in, out;
        char *grep_args[] = {"grep", "Sri Lanka", NULL};

        // open input and output files
        in = open("fixtures", O_RDONLY);
        out = open("out", O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);

        // replace standard input with input file
        dup2(in, STDIN_FILENO);

        printf("%d %d\n", in, out);
        
        // replace standard output with output file
        dup2(out, STDOUT_FILENO);

        // close unused file descriptors
        close(in);
        close(out);

        // execute grep
        execvp("grep", grep_args);
}
