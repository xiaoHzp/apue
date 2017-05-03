#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

char *env_init[] = {"USER=unknow","PATH=/home/adtim/apue/ch8",NULL};

int main()
{
	pid_t pid;
	
	if((pid = fork()) < 0)
		return -1;
	else if(pid == 0)
	{
		if(execle("/home/adtim/apue/ch8/test1","test1","arg1","arg2",(char*)0,env_init) < 0)
			return -1;
	}

	if(waitpid(pid,NULL,0) < 0)
		return -1;

	if((pid = fork()) < 0)
		return -1;
	else if(pid == 0)
	{
		if(execl("/home/adtim/apue/ch8/test1","test1","only 1 arg",(char*)0) < 0)
			return -1;
	}
	
	if(waitpid(pid,NULL,0) < 0)
		return -1;
	return EXIT_SUCCESS;
}
