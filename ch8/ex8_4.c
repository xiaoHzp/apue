#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void pr_wait(int);

int main()
{
	pid_t pid;
	int status;

	if((pid = fork()) < 0)
		return -1;
	else if(pid == 0)
		exit(7);

	if(wait(&status) != pid)
		return -1;
	pr_wait(status);

	if((pid = fork()) < 0)
		return -1;
	else if(pid == 0)
		abort();

	if(wait(&status) != pid)
		return -1;
	pr_wait(status);

	if((pid = fork()) < 0)
		return -1;
	else
		status /= 0;

	if(wait(&status) != pid)
		return -1;
	pr_wait(status);
	return EXIT_SUCCESS;
}

void pr_wait(int status)
{
	if(WIFEXITED(status))
		printf("normal termination,exit status = %d\n",WEXITSTATUS(status));
	else if(WIFSIGNALED(status))
		printf("abnormal termination,signal number = %d%s\n",
				WTERMSIG(status),
	#ifdef	WCOREDUMP
				WCOREDUMP(status)?"(core file generated)":"");
	#else
			"");
	#endif
	else if(WIFSTOPPED(status))
		printf("child stopped,signal number = %d\n",WSTOPSIG(status));

}
