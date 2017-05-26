#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static void sig_quit(int);

int main()
{
	sigset_t newset,oldset,pendset;
	if(signal(SIGQUIT,sig_quit) == SIG_ERR)
		return -1;
	sigemptyset(&newset);
	sigaddset(&newset,SIGQUIT);
	if(sigprocmask(SIG_BLOCK,&newset,&oldset) < 0)
		return -1;
	sleep(6);

	if(sigpending(&pendset) < 0)
		return -1;
	if(sigismember(&pendset,SIGQUIT))
		printf("\nSIGQUIT pending\n");

	if(sigprocmask(SIG_SETMASK,&oldset,NULL) < 0)
		return -1;
	printf("SIGQUIT unblocked\n");

	sleep(6);
	exit(0);
}

static void sig_quit(int signo)
{
	printf("caught SIGQUIT\n");
	if(signal(SIGQUIT,SIG_DFL) == SIG_ERR)
		return;
}
