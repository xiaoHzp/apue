#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>

static void						sig_usr1(int);
static void						sig_alrm(int);
static sigjmp_buf				jmpbuf;
static volatile sig_atomic_t	canjump;

void pr_mask(const char*);
int main()
{
	if(signal(SIGUSR1,sig_usr1) == SIG_ERR)
		return -1;
	if(signal(SIGALRM,sig_alrm) == SIG_ERR)
		return -1;
	pr_mask("starting main:");
	if(sigsetjmp(jmpbuf,1))
	{
		pr_mask("endind main:");
		exit(0);
	}
	
	canjump = 1;
	for(;;)
		pause();
}

static void sig_usr1(int signo)
{
	time_t starttime;
	if(canjump == 0)
		return;
	pr_mask("starting sig_usr1:");
	alarm(3);
	starttime = time(NULL);
	for(;;)
		if(time(NULL) > starttime + 5)
			break;
	pr_mask("finishing sig_usr1:");
	canjump = 0;
	siglongjmp(jmpbuf,1);
}

static void sig_alrm(int signo)
{
	pr_mask("in sig_alrm:");
}
void pr_mask(const char* str)
{
	sigset_t set;
	int errno_save;
	errno_save = errno;
	if(sigprocmask(0,NULL,&set) < 0)
		return;
	else
	{
		printf("%s ",str);
		if(sigismember(&set,SIGINT))
			printf(" SIGINT");
		if(sigismember(&set,SIGALRM))
			printf(" SIGALRM");
		if(sigismember(&set,SIGUSR1))
			printf(" SIGUSR1");
		printf("\n");
	}
	errno = errno_save;
}
