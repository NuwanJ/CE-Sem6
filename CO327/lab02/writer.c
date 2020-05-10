#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
   int fd;
   char* fifo = "/tmp/fifo";
   char buff[256];

   mkfifo(fifo,0666);

   fd = open(fifo, O_WRONLY);
   write(fd, "Hi",2);
   close(fd);

   unlink(fifo);

   /*
   char* input = "/tmp/input";
   char* output = "/tep/output";
   char buff[256];
   char buff2[256];

   inputFd = open(input, O_WRONLY); // Write into input FIFO
   outputFd = open(output, O_RDONLY); // Read from the output FIFO

   while(1){
   fgets(buff, 255, stdin);        // read a line from stdin
   printf("stdin: %s", buff);

   write(inputFd, buff, strlen(buff));
   read(outputFd, buff2, 255);

   printf("FIFO: %s\n", buff2);

}

*/



return 0;
}
