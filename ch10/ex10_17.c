#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>


void abort(void)
{
	sigset_t mask;
	struct sigaction action;
	
	sigaction(SIGABRT,NULL,&action); // 获取当前处理ABRT的方式
	if(action.sa_handler == SIG_IGN)
	{
		action.sa_handler = SIG_DFL; // 如果是忽略则设置成默认
		sigaction(SIGABRT,&action,NULL);
	}

	if(action.sa_handler == SIG_DFL)
		fflush(NULL);  // 刷新流

	sigfillset(&mask);
	sigdelset(&mask,SIGABRT); // 确保打开SIGABRT信号处理
	sigprocmask(SIG_SETMASK,&mask,NULL); // 除SIGABRT以外其他所有都阻塞
	kill(getpid(),SIGABRT);  // 发送信号

	fflush(NULL); // 如果一开始abort的信号处理程序是自定义的就会返回到这里。
	action.sa_handler = SIG_DFL;
	sigaction(SIGABRT,&action,NULL);
	sigprocmask(SIG_SETMASK,&mask,NULL);
	kill(getpid(),SIGABRT);
	exit(1); // 不会进行到这里，在调用默认信号处理程序时会终止
}
int main()
{
	exit(0);
}
