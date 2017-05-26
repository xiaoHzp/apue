#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

volatile sig_atomic_t quitflag; // set nonzero by signal handler

static void sig_int(int signo)
{
	if(signo == SIGINT)
		printf("\ninterrupt\n");
	else if(signo == SIGQUIT)
		quitflag = 1; // set flag for main loop
}
int main()
{
	sigset_t newmask,oldmask,zeromask;
	if(signal(SIGINT,sig_int) == SIG_ERR)
		return -1;
	if(signal(SIGQUIT,sig_int) == SIG_ERR)
		return -1;

	sigemptyset(&zeromask);
	sigemptyset(&newmask);
	sigaddset(&newmask,SIGQUIT);

	// block SIGQUIT and save current signal mask
	if(sigprocmask(SIG_BLOCK,&newmask,&oldmask) < 0)
		return -1;
	while(quitflag == 0)
		sigsuspend(&zeromask);
	// SIGQUIT has been caught and is now blocked;do whatever
	quitflag = 0;

	if(sigprocmask(SIG_SETMASK,&oldmask,NULL) < 0)
		return -1;
	exit(0);
}
