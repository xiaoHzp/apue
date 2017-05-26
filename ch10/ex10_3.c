#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void sig_usr(int);

int main()
{
	if(signal(SIGUSR1,sig_usr) == SIG_ERR)
		return -1;
	if(signal(SIGUSR2,sig_usr) == SIG_ERR)
		return -1;
	for(;;)
		pause();
	return EXIT_SUCCESS;
}

void sig_usr(int signo)
{
	switch(signo)
	{
		case SIGUSR1:
			printf("received SIGUSR1\n");
			break;
		case SIGUSR2:
			printf("received SIGUSR2\n");
			break;
		default:
			printf("receive signal: %d\n",signo);
	}
}
