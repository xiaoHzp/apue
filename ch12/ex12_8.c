#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>

int quitflag = 0;
sigset_t mask;

pthread_cond_t waitloc = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* thr_fn(void* arg)
{
	int err,signo;

	while(1)
	{
		err = sigwait(&mask,&signo);
		if(err != 0)
			exit(-1);
		switch(signo)
		{
			case SIGQUIT:
				pthread_mutex_lock(&mutex);
				quitflag = 1;
				pthread_cond_signal(&waitloc);
				pthread_mutex_unlock(&mutex);
				return 0;
			case SIGINT:
				printf("\ninterrupt\n");
				break;
			default:
				printf("unexpected signal %d\n",signo);
				exit(1);
		}
	}	
}

int main()
{
	int err;
	sigset_t oldset;
	pthread_t tid;

	sigemptyset(&mask);
	sigaddset(&mask,SIGQUIT);
	sigaddset(&mask,SIGINT);

	err = pthread_sigmask(SIG_BLOCK,&mask,&oldset);
	err = pthread_create(&tid,NULL,thr_fn,NULL);

	pthread_mutex_lock(&mutex);
	while(quitflag == 0)
		pthread_cond_wait(&waitloc,&mutex);
	pthread_mutex_unlock(&mutex);

	quitflag = 0;

	err = pthread_sigmask(SIG_SETMASK,&oldset,NULL);
	exit(0);
}
