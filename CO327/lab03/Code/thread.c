#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void *thread_function(void *arg)
{
	int a;
	for(a = 0;a < 5; a++){
		printf("Thread says hi!\n");
		sleep(1);
	}
	return NULL;
}
int main(void)
{
	pthread_t mythread, mythread2;

	if (pthread_create(&mythread, NULL, thread_function, NULL)){
		printf("error creating thread.");
		abort();
	}
	if (pthread_create(&mythread2, NULL, thread_function, NULL)){
		printf("error creating thread.");
		abort();
	}

	printf("Threads are called separately\n");

	if (pthread_join(mythread, NULL)){
		printf("error joining thread.");
		abort();
	}
	printf("Main thread says hi!\n");
	exit(0);
}


/*

a) Why do you need '-pthread' flag when you compile?

-pthread is a flag in GCC for inform the compiler to link the POSIX Threads library while compiling.
If it isn't


https://gcc.gnu.org/onlinedocs/gcc/Link-Options.html

*/
