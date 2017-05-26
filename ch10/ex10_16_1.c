#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>

static void sig_int(int);
void pr_mask(const char*);
int main()
{
	sigset_t newmask,oldmask,waitmask;
	pr_mask("program start: ");
	if(signal(SIGINT,sig_int) == SIG_ERR)
		return -1;
	sigemptyset(&newmask);
	sigemptyset(&waitmask);
	sigaddset(&newmask,SIGINT);
	sigaddset(&waitmask,SIGUSR1);

	if(sigprocmask(SIG_BLOCK,&newmask,&oldmask) < 0)
		return -1;

	pr_mask("in critical region: ");

	if(sigsuspend(&waitmask) != -1)
		return -1;

	pr_mask("after return from sigsuspend: ");

	if(sigprocmask(SIG_SETMASK,&oldmask,NULL) < 0)
		return -1;

	pr_mask("program exit: ");
	exit(0);
}

static void sig_int(int signo)
{
	pr_mask("\nin sig_int:");
}
void pr_mask(const char *str)
{
	int errno_save;
	sigset_t set;
	errno_save = errno;
	if(sigprocmask(0,NULL,&set) < 0)
		return;
	else
	{
		printf("%s ",str);
		if(sigismember(&set,SIGINT))
			printf(" SIGINT");
		if(sigismember(&set,SIGUSR1))
			printf(" SIGUSR1");
		printf("\n");
	}
	
	errno = errno_save;
}
