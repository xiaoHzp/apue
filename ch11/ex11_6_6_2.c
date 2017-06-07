#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NTR 4
int num = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  cond  = PTHREAD_COND_INITIALIZER;

void* thr_fn(void* arg)
{
	long n = (long)arg;
	while(1)
	{
		pthread_mutex_lock(&mutex);
		char c = 'a' + n;
		while(num!=n)
			pthread_cond_wait(&cond,&mutex);
		printf("%c",c);
		if(num == 3)
			printf("\n");
		num =( num + 1 ) % NTR;
		pthread_cond_broadcast(&cond);
		pthread_mutex_unlock(&mutex);
	}
}

int main()
{
	pthread_t tid[NTR];
	long i;
	for(i = 0; i < NTR; i++)
		pthread_create(tid+i,NULL,thr_fn,(void*)i);
	alarm(6);
	for(i = 0; i < NTR; i++)
		pthread_join(tid[i],NULL);
	exit(0);
}
