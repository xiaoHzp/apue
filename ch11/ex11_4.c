#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void printid(const char* s)
{
	pid_t pid;
	pthread_t tid;

	pid = getpid();
	tid = pthread_self();
	printf("%s pid %lu tid %lu (0x%lx)\n",s,(unsigned long)pid,(unsigned long)tid,(unsigned long)tid);
}

void* thr_fn(void *arg)
{
	printid("new thread:");
	return (void*)0;
}

int main()
{
	int err;
	pthread_t ntid;
	err = pthread_create(&ntid,NULL,thr_fn,NULL);
	if(err != 0){
		printf("can't create thread\n");
		return -1;
	}
	printid("main thread:");
	sleep(1);
	exit(0);
}
