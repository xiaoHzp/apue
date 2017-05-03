#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
it main(int argc,char*argv[])
{
	pid_t	pid;
	if((pid = fork()) < 0)
		return -1;
	else if(pid == 0)
	{
		printf("I am the first child process.pid:%d\tppid:%d\n",getpid(),getppid());
		pid = fork();
		if(pid < 0)
			return -1;
		else if(pid > 0)
		{
			printf("first process is exited.\n");
			exit(0);
		}

		sleep(2);
		printf("I am the second child process.pid:%d\tppid:%d\n",getpid(),getppid());
		exit(0);
	}
	if(waitpid(pid,NULL,0) !=pid)
		return -1;
	sleep(3);
	return EXIT_SUCCESS;
}
