#include "mytimer.h"

static void disable_interrupt(void)  // 关闭中断
{
	sigemptyset(&newmask);
	sigaddset(&newmask,SIGINT);
	if(sigprocmask(SIG_BLOCK,&newmask,&oldmask) < 0)
		fprintf(stderr,"sigprocmask error\n");
}

static void enable_interrupt(void) // 开启中断
{
	if(sigprocmask(SIG_SETMASK,&oldmask,NULL) < 0)
		fprintf(stderr,"sigprocmask error\n");
}

void timer_init(void)
{
	int i;
	disable_interrupt();
	for(i = 0;i<MAX_TIMERS;i++)
		timers[i].inuse = FALSE; // 将计时器数组中每个计时器inuse状态设置为未用
	
	sigfillset(&newact.sa_mask); // 在处理信号时，阻塞所有信号的递送
	newact.sa_flags = 0;
	newact.sa_handler = timer_out_handler;
	if(sigaction(SIGALRM,&newact,&oldact) < 0)
	{
		fprintf(stderr,"sigaction error\n");
		enable_interrupt();
		return;
	}
	enable_interrupt();
}

struct timer* timer_declare(TIME time_s,timer_handler *handler,void *arg)
{
	int i;
	disable_interrupt();
	for(i = 0;i<MAX_TIMERS;i++) // 找到第一个未用的计时器
		if(!timers[i].inuse)
			break;
	if(i == MAX_TIMERS) // 所有计时器都已用完
	{
		enable_interrupt();
		return NULL;
	}
	timers[i].time = time_s; // 计时器时间
	timers[i].ahandler = handler; // 计时器处理函数
	timers[i].arg = arg; // 处理函数参数
	
	if(!timer_next) // 当前计时器为唯一计时器
	{
		time_set = time(NULL); // 保存当前设置时间
		alarm((timer_next = &timers[i])->time); // 开始计时
	}else if(time_s  < (timer_next->time - (time(NULL) - time_set))) // 比较当前计时器和当前正在计时的计时器的时间长度
	{
		timer_update(); // 更新每个计时器的计时
		timer_next = &timers[i]; // 设置新的当前正在计时的计时器
		time_set = time(NULL); // 记录设置时间
		alarm(timer_next->time); // 开始计时
	}
	timers[i].inuse = TRUE; // 最后再改变inuse防止update干扰
	enable_interrupt();
	return &timers[i];
}

void timer_undeclare(struct timer* t)
{
	disable_interrupt();
	if(!t->inuse)
	{
		enable_interrupt();
		return;
	}
	
	t->inuse = FALSE;
	
	if(t == timer_next) // 如果是当前正在计时的计时器
		timer_update();

	enable_interrupt();
}

void timer_update() // 更新所有计时器时间，并将时间最短的设置为当前正在计时的计时器。
{
	disable_interrupt();
	int i;
	static struct timer timer_last = {FALSE,VERY_LONG_TIME,NULL,NULL};
	timer_next = &timer_last;
	time_now = time(NULL); // 读取当前时间
	for(i = 0;i<MAX_TIMERS;i++)
	{
		if(timers[i].inuse)
		{
			timers[i].time -= time_now - time_set; // 所有计时更新
			if(timers[i].time < timer_next->time)
				timer_next = &timers[i]; // 更新当前正在计时的计时器
		}
	}
	if(timer_next->inuse) // 如果存在还未发生的定时器
	{
		alarm(timer_next->time);
		time_set = time(NULL);
	}else
		timer_next = NULL;
	enable_interrupt();
}

void timer_out_handler(int signo)
{
	timer_next->ahandler(timer_next->arg);
	timer_next->inuse = FALSE;
	timer_update(); // 寻找下一个执行的定时器
}

void func(void* arg)
{
	char *p = (char*)arg;
	printf("%s\n",p);
}
