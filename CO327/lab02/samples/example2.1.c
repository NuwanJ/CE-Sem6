#include <stdio.h>
#include <unistd.h>

#define READ 0
#define WRITE 1

int main()
{
	int pipe_ends[2];
	pid_t pid;
	int status;

	if(pipe(pipe_ends)){
		perror("Create pipe");
		return -1;
	}

	pid = fork();
	if(pid < 0){
		perror("Fork");
		return -1;
	}

	if(pid > 0){
		/* parent */
		close(pipe_ends[READ]);
		write(pipe_ends[WRITE],"Hello!\n",8);
		write(pipe_ends[WRITE],"hello!\n",8);
		close(pipe_ends[WRITE]);
	}

	if(pid == 0){
		/* child */
		char buff[128];
		close(pipe_ends[WRITE]);
		sleep(5);
		int count = read(pipe_ends[READ], buff, 128);
		buff[count] = '\0';
		printf("%s",buff);
	}

	wait(&status);
	return 0;
}
