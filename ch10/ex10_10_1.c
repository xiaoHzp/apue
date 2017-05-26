/*

	此sleep函数会影响交互信号处理，即会提早终止对其他信号的处理	

*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>
#include <unistd.h>

unsigned int sleep2(unsigned int);
static void sig_int(int);

static jmp_buf env_alarm;
int main()
{
	unsigned int upslept;
	if(signal(SIGINT,sig_int) == SIG_ERR)
		return -1;
	upslept = sleep2(5);
	printf("sleep2 returned: %u\n",upslept);
	exit(0);	
}

static void sig_int(int signo)
{
	int		i,j;
	volatile int k;
	printf("\nsig_int starting\n");
	for(int i = 0;i<300000;i++)
		for(int j = 0;j<4000;j++)
			k += i*j;
	printf("sig_int finished\n");
}

static void sig_alrm(int signo)
{
	longjmp(env_alarm,1);
}
unsigned int sleep2(unsigned int seconds)
{
	if(signal(SIGALRM,sig_alrm) == SIG_ERR)
		return -1;
	if(setjmp(env_alarm) == 0)
	{
		alarm(seconds);
		pause();
	}
	return alarm(0);
}
