#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int		globvar = 8;
char	buf[]	= "a write to stdout\n";

int main()
{
	int		var;
	pid_t	pid;
	
	var = 88;
	if(write(STDOUT_FILENO,buf,sizeof(buf)-1)!=sizeof(buf) -1 )
	{
		perror("write error\n");
		return -1;
	}
	printf("before fork\n");
	if((pid = fork()) < 0)
	{
		printf("fork error\n");
		return -1;
	}else if(pid == 0)
	{
		++var;
		++globvar;
	}else
		sleep(2);
	printf("123\n");
	printf("pid = %ld,glob = %d,var = %d\n",(long)getpid(),globvar,var);
	return EXIT_SUCCESS;
}
