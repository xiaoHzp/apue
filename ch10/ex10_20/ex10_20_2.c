/*

	测试信号队列

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
	struct sigaction newact,oldact;
	sigset_t newmask,oldmask;
	newact.sa_handler = sig_int;
	newact.sa_flags = 0;
	sigemptyset(&newact.sa_mask);
//	if(sigaction(SIGINT,&newact,&oldact) < 0)
//		return -1;
	sigemptyset(&newmask);
	sigaddset(&newmask,SIGRTMIN);
//	sigaddset(&newmask,SIGINT);
	sigprocmask(SIG_BLOCK,&newmask,&oldmask);

//	signal(SIGINT,sig_int);
	signal(SIGRTMIN,sig_int);
	
	union sigval val;
	val.sival_int = 100;
	sigqueue(getpid(),SIGRTMIN,val);
	sigqueue(getpid(),SIGRTMIN,val);
	sigqueue(getpid(),SIGRTMIN,val);
	sleep(3);

	sigprocmask(SIG_SETMASK,&oldmask,NULL);
	exit(0);
}
