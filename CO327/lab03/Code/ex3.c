#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void *thread_function(void *arg){
   int a;
   for(a = 1; a <= 3; a++){
      printf("Thread %d:%d says hi!\n", *(int *)arg, a); // ,*(int *)(arg+4)
      sleep(1);
   }
   (*(int *)arg)++;
   return NULL;
}

int main(void){
   pthread_t mythread;
   int i, count = 1, myCount=1;

   for (i = 0; i < 5; i++){
      if ( pthread_create( &mythread, NULL, thread_function, &count) ){
         printf("error creating thread.");
         abort();
      }
      myCount++;
      /*if ( pthread_join ( mythread, NULL ) ){
         printf("error joining thread.");
         abort();
      }*/
      sleep(1);
      //printf("\n");
   }
   sleep(1);  // 5

   printf("Main thread says hi!\n");
   exit(0);
}

/*


*/
