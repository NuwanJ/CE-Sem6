#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "sys/types.h"

void *thread_function(void *arg)
{
	printf("Thread says hi!\n");
	return NULL;
}

int main(void)
{
	pthread_t mythread;
	int i;

	for(i = 0; i < 3; i++){
		if (pthread_create(&mythread, NULL, thread_function, NULL)){
			printf("error creating thread.");
			abort();
		}
	}

	if (pthread_join(mythread, NULL)){
		printf("error joining thread.");
		abort();
	}

	printf("Main thread says hi!\n");
	exit(0);
}
