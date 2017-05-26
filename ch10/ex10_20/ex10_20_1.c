/*

	测试linux默认是否信号排队

 */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void sig_int(int signo)
{
	printf("\nSIGINT\n");
}

int main()
{
	sigset_t		 newmask,oldmask;
	struct sigaction newact,oldact;

	newact.sa_handler = sig_int;
	newact.sa_flags = 0;
	sigemptyset(&newact.sa_mask);
	if(sigaction(SIGINT,&newact,&oldact) < 0)
		return -1;

	sigemptyset(&newmask);
	sigaddset(&newmask,SIGINT);
	sigprocmask(SIG_BLOCK,&newmask,&oldmask);

	sleep(6);

	sigprocmask(SIG_SETMASK,&oldmask,NULL);
	exit(0);
}
