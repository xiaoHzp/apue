#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <limits.h>

#define TRUE  1
#define FALSE 0
#define MAX_TIMERS 100 // 最大定时器数
#define VERY_LONG_TIME LONG_MAX // 最长定时数

typedef time_t TIME; // 隐藏TIME的实现
typedef void timer_handler(void *arg); 

volatile TIME time_now,time_set; // now为当前时间,set为当前定时器设置时间

struct sigaction newact,oldact; // 设置sigalrm的处理程序
sigset_t newmask,oldmask; // 设置屏蔽字

struct timer
{
	int inuse; // true if in use
	TIME time; // relative time to wait
	timer_handler *ahandler; // called when the timer has expired
	void *arg; // arguemtn of handler
}timers[MAX_TIMERS];
struct timer *timer_next;

void  timer_init(void); // 初始化计时器
struct timer* timer_declare(TIME,timer_handler*,void*); // 生成一个计时器
void timer_undeclare(struct timer*); // 取消一个计时器
void timer_update(); // 更新计时器数组，并获得下一个将要计时的计时器
void timer_out_handler(int signo); // 信号处理函数
void func(void *arg); // 自定义输出函数
