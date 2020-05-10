/*

Answer for Exercise 3.1

'exec' is a function that replaces current process image with a new process image provided as the argument for it.
Thereefore all the communication with the parent process will be lost. (No parent child relationship after that command)

*/

#include "sys/types.h"
#include "sys/wait.h"
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

int main(int argc, char const *argv[]) {

   pid_t pid;

   if (pid <0) {
      perror("Fork failed");
      exit(1);

   } else if (pid == 0) {
      // Child
      execl("/bin/ls", "-l", argv[1], NULL);
      // This command will replace the child process's image. So it only retuns if there any error.
      // No way to send the result to the parent 

   } else {
      // Parent
      wait(NULL);
   }


   return 0;
}
