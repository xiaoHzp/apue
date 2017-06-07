#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

struct msg{
	struct msg *m_next;
};

struct msg *workq;

pthread_cond_t qready = PTHREAD_COND_INITIALIZER;
pthread_mutex_t qlock = PTHREAD_MUTEX_INITIALIZER;

void process_msg(void)
{
	struct msg *mp;
	for(;;){
		pthread_mutex_lock(&qlock);
		while(workq == NULL)
			pthread_cond_wait(&qready,&qlock);
		mp = workq;
		workq = mp->m_next;
		pthread_mutex_unlock(&qlock);
	}
}

void enqueue_msg(struct msg* mp)
{
	pthread_mutex_lock(&qlock);
	mp->m_next = workq;
	workq = mp;
	pthread_cond_signal(&qready);
	pthread_mutex_unlock(&qlock);
}

int main()
{
	exit(0);
}
