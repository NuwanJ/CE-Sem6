#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include "sys/wait.h"

int main(int argc, char**argv){
    int sockfd,newsockfd,n,c=0;
    struct sockaddr_in servaddr,cliaddr;
    socklen_t clilen;
    char outBuffer[1000];
    char inBuffer[1000];
    pid_t pid;

    /* one socket is dedicated to listening */
    sockfd=socket(AF_INET,SOCK_STREAM,0);

    /* initialize a sockaddr_in struct with our own address information for binding the socket */
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(12345);

    /* binding */
    bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
    listen(sockfd,0);
    clilen=sizeof(cliaddr);

    while(1){
        newsockfd = accept(sockfd,(struct sockaddr *) &cliaddr, &clilen); // the uninitialized cliaddr variable is filled in with the

        if(newsockfd<0){
            perror("ERROR on accept");
            exit(1);
        }

        pid = fork();

        if(pid<0){
            perror("Error on Fork");
            exit(1);
        }

        if(pid==0){
            // Child process
            while(1){
                sprintf(outBuffer, "Enter an URL: ");
                ssize_t resp = sendto(newsockfd,outBuffer,strlen(outBuffer),0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));

                if(resp<0){
                    perror("Client Disconnected");
                    exit(1);
                }
                
                n = recvfrom(newsockfd,inBuffer,1000,0,(struct sockaddr *)&cliaddr,& clilen);// information of the client by recvfrom function
                printf(">> %d > File URL: %s\n", getpid(),inBuffer);
                // remove \n char at the end
                inBuffer[strlen(inBuffer)-1] = 0;

                FILE *fp = fopen(inBuffer, "r");
                int fileSize = 0, i=0,j=0;
                int blockSize = 1000;
                char file[1000000];
                char symbol;

                if(fp != NULL){
                    while((symbol = getc(fp)) != EOF){
                        file[fileSize]= symbol;
                        fileSize++;
                    }

                    while(i<fileSize){
                        // Copy the file block by block into the outBuffer
                        for(j=0;(j<blockSize && i<fileSize) ;j++){
                            outBuffer[j] = file[i++];
                        }
                        outBuffer[j] = 0;

                        printf(">> Sending: %s \n",outBuffer);
                        sendto(newsockfd,outBuffer,strlen(outBuffer),0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
                    }
                    fclose(fp);
                }else{
                    sprintf(outBuffer, "Error: invalid URL\n");
                    sendto(newsockfd,outBuffer,strlen(outBuffer),0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
                }
            }
            close(newsockfd);
            exit(0);

        }else{
            // Parent process
            //wait(NULL);
            close(newsockfd);
        }

    }
    return 0;
}


/*
Result
----------------------------

2.
If wait() is introduced to the given location, new client can't connect to the server until previous client is disconnected.

3.
Client program will be disconnect from the server on next input.
But unable to restart for some time.

4.





----------------------------
*/
