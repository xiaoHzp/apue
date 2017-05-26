#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

int main()
{
//	printf("%s\n",strsignal(SIGINT)); // 测试strsignal函数
	psignal(SIGINT,"test"); // 测试psignal函数
	return 0;
}
