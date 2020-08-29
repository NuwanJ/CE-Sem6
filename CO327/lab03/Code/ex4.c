#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

void* handle_client(void*);

int main(){
   int listenfd;
   int* connfd;
   struct sockaddr_in servaddr,cliaddr;
   socklen_t clilen;
   pthread_t client_thread;

   listenfd=socket(AF_INET,SOCK_STREAM,0);

   servaddr.sin_family = AF_INET;
   servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
   servaddr.sin_port=htons(32000);

   bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));

   listen(listenfd,5);

   clilen = sizeof(cliaddr);
   while (1){
      connfd = malloc(sizeof(int));
      *connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen);

      if (*connfd < 0) error("Error on accept");

      if ( pthread_create( &client_thread, NULL, handle_client, connfd) ){
         printf("error creating thread.");
         abort();
      }
   }
}

void* handle_client(void* connfd){
   /* read a string sent by the client,
   * print it and then send the string
   * "Hello from the server" to the client*/

   int socket = *(int*)connfd;
   char inBuffer[1000];
   char outBuffer[1000];

   // Read and send back the input string
   int n = recvfrom(connfd,inBuffer,1000,0,(struct sockaddr *)&cliaddr,& clilen);
   //sendto(connfd,inBuffer,strlen(inBuffer),0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
   write(socket, inBuffer, strlen(inBuffer));

   // Send "Hello from the server"
   sprintf(outBuffer, "\nHello from the server\n");
   //sendto(connfd,outBuffer,strlen(outBuffer),0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
   write(socket, outBuffer, strlen(outBuffer));

   printf("Send a message to the client");

   free(connfd);
   return NULL;
}
