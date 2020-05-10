#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {

   if(argc<2){
      printf("No enough arguments\n");
      return 1;
   }

   int in;
   char c;

   printf("reading from %s\n", argv[1]);

   // Open the file need to read
   in = open(argv[1], O_RDONLY);
   if(in<0){
      fprintf(stderr,"Couldn't open the file for read\n");
      return 1;
   }

   while(read(in,&c,sizeof(char))>0){
      // Read char by char and print into STDOUT
      //fprintf(stdout,"%c", c);
      write(STDOUT_FILENO, &c, sizeof(char));
   }

   if(close(in) == -1){
      fprintf(stderr,"Error closing the file after reading.\n");
      return 1;
   }

   return 0;
}
