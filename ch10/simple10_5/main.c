#include "mytimer.c"

int main()
{
	setbuf(stdout,NULL);
	timer_init();
	TIME time = 1;
	timer_declare(time,func,(void*)"hello world");
	time = 3;
	struct timer* t =timer_declare(time,func,(void*)"this is a test");
	time = 5;
	struct timer* m = timer_declare(time,func,(void*)"func(5)");
	timer_undeclare(t);
	while(1)
		pause();
	exit(0);
}
