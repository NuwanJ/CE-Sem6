#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
      int i;
      close(pipe_parent2child[READ_END]);
      close(pipe_child2parent[WRITE_END]);

      char buff[128];

      while(1){
         gets(buff);    // Read a line from stdin

         printf("write %s to the chile\n", buff);
         write(pipe_parent2child[WRITE_END], buff, strlen(buff));
         sleep(1);
      }
   }

   if(pid == 0){
      /* child : reads input pipe and write the capitalized chars to output pipe*/
      char buff[128];
      int count;
      close(pipe_parent2child[WRITE_END]);
      close(pipe_child2parent[READ_END]);

      while((count = read(pipe_parent2child[READ_END], buff, 128)) > 0) {

         for(int i=0;i<count;i++){
            buff[i] = toupper(buff[i]);
         }
         write(pipe_child2parent[WRITE_END], buff, strlen(buff));
         //write(STDOUT_FILENO, &buff, count);
         sleep(2);
      }
   }
   return 0;
}
