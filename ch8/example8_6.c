#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	pid_t pid;

	if((pid = fork()) < 0)
		return -1;
	else if(pid == 0)
	{
			exit(0);
	}
	system("ps");
	sleep(6);
	exit(0);
}

