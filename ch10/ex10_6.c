#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pwd.h>
#include <string.h>
#include <unistd.h>

static void my_alarm(int signo)
{
	struct passwd *rootptr;
	if((rootptr = getpwnam("root")) == NULL)
		exit(-1);
//	alarm(1);
}
int main()
{
	struct passwd *ptr;
	signal(SIGALRM,my_alarm);
	alarm(1);
//	for(;;)
//	{
		if((ptr = getpwnam("adtim")) == NULL)
			exit(-1);
		if(strcmp(ptr->pw_name,"adtim") != 0)
			printf("return value corrupted!,pw_name = %s\n",ptr->pw_name);
//	}
	return EXIT_SUCCESS;
}
