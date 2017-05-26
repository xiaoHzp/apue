/*

	这里也是存在对其他信号处理程序有影响，会提早结束对其它信号的处理

*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <setjmp.h>
#include <signal.h>

static jmp_buf	env_jmp;
static void sig_alrm(int);

int main()
{
	int n;
	char line[1000];
	if(signal(SIGALRM,sig_alrm) == SIG_ERR)
		return -1;
	if(setjmp(env_jmp) !=0)
	{
		printf("read timeout\n");
		exit(-1);
	}
	alarm(10);
	if((n = read(STDIN_FILENO,line,1000)) < 0)
		return -1;
	alarm(0);

	write(STDOUT_FILENO,line,n);
	exit(0);
}

static void sig_alrm(int signo)
{
	longjmp(env_jmp,1);
}
