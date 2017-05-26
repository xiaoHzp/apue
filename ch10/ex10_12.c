#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>

void pr_mask(const char*);
int main()
{
	sigset_t set,oset;
	sigemptyset(&set);
	sigaddset(&set,SIGINT);
	sigprocmask(SIG_BLOCK,&set,&oset);
	pr_mask("current:");
	exit(0);
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
		if(sigismember(&set,SIGQUIT))
			printf(" SIGQUIT");
		if(sigismember(&set,SIGUSR1))
			printf(" SIGUSR1");
		if(sigismember(&set,SIGALRM))
			printf(" SIGALRM");
		printf("\n");
	}
	errno = errno_save;
}
