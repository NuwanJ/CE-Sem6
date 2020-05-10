#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_SIZE 1024

void die(const char *msg);

int main(int argc, char const *argv[]) {

   int fd;
   char* fifo = "/tmp/fifo";
   char buf[MAX_SIZE];

   mkfifo(fifo,0666);

   fd = open(fifo, O_RDONLY);
   read(fd, buf, MAX_SIZE);
   printf("message read = %s\n", buf);
   close(fd);

   /*
   char* input = "/tmp/input";
   char* output = "/tep/output";
   char *tr_args[] =  {"tr", "[a-z]]", "[A-Z]", NULL};

   int inputFd, outputFd;

   mkfifo(input, 0666);
   mkfifo(output, 0666);

   inputFd = open(input, O_RDONLY);
   outputFd = open(output, O_WRONLY);

   // Change standard input and output with FIFO input and output
   if(dup2(inputFd, STDIN_FILENO)==-1) die("dup(input)");
   if(dup2(outputFd, STDOUT_FILENO)==-1) die("dup(outut)");

   if(execvp("tr", tr_args) == -1) die("execvp(tr)");
   printf("Error\n");
*/

   return 0;
}

void die(const char *msg) {
   perror(msg);
   exit(EXIT_FAILURE);
}
