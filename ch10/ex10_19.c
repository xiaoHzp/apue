#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void sig_alrm(int signo)
{
	
}

unsigned int sleep(unsigned int second)
{
	sigset_t newmask,oldmask,susmask;
	struct sigaction newact,oldact;
	unsigned int upslept;

	newact.sa_handler = sig_alrm;
	newact.sa_flags = 0;
	sigemptyset(&newact.sa_mask);
	sigaction(SIGALRM,&newact,&oldact);

	sigemptyset(&newmask);
	sigaddset(&newmask,SIGALRM);
	sigprocmask(SIG_BLOCK,&newmask,&oldmask);

	susmask = oldmask;
	
	alarm(second);
	sigdelset(&susmask,SIGALRM);

	sigsuspend(&susmask);

	upslept = alarm(0);
	sigaction(SIGALRM,&oldact,NULL);
	sigprocmask(SIG_SETMASK,&oldmask,NULL);
	return upslept;
}
int main()
{
	exit(0);
}
