#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char const *argv[]) {

   if(argc<3){
      printf("No enough arguments\n");
      return 1;
   }

   int in, out;
   char c;

   printf("copy from '%s' to '%s'\n", argv[1], argv[2]);

   // Open the file need to read
   in = open(argv[1], O_RDONLY);
   if(in<0){
      fprintf(stderr,"Couldn't open the file for read\n");
      return 1;
   }

   out = open(argv[2], O_WRONLY | O_CREAT , S_IRUSR | S_IWUSR );
   if(out<0){
      fprintf(stderr,"Couldn't open the file for writing\n");
      return 1;
   }

   while(read(in,&c,1)>0){
      // Read char by char and write into destination file
      size_t ret = write(out,&c,sizeof(char));

      if((int)ret == -1){
         fprintf(stderr,"Error writing to file\n");
         return 1;
      }
   }


	if(close(out) == -1){
		fprintf(stderr,"Error closing the file after writing.\n");
		return 1;
	}

   if(close(in) == -1){
      fprintf(stderr,"Error closing the file after reading.\n");
      return 1;
   }

   return 0;
}
