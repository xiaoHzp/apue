#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void f1(void);
static void f2(void);

int main()
{
	f1();
	f2();
	_exit(0);
}

static void f1(void)
{
	if(fork() < 0)
		return ;
}

static void f2(void)
{
	char buf[1000];
	int i;
	for(i = 0;i < 1000; i++)
		buf[i] = 0;
}
