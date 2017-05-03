#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void print_s(siginfo_t);
int main()
{
	pid_t pid;
	siginfo_t siginfo;

	if((pid = fork()) < 0)
		return -1;
	else if(pid == 0)
		exit(7);

	if(waitid(P_PID,pid,&siginfo,WEXITED) == -1)
		return -1;
	print_s(siginfo);

	if((pid = fork()) < 0)
		return -1;
	else if(pid == 0)
		abort();

	if(waitid(P_PID,pid,&siginfo,WEXITED) == -1)
		return -1;
	print_s(siginfo);
	return EXIT_SUCCESS;
}

void print_s(siginfo_t s)
{
	printf("signal number:%d\n",s.si_signo);
	printf("cause of the signal:%d\n",s.si_code);
	printf("signal value:%d\n",s.si_value.sival_int);
}
