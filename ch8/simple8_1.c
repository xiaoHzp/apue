#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int globvar = 6;
int main()
{
	int var = 88;
	pid_t pid;

	if((pid = vfork()) < 0)
		return -1;
	else if(pid == 0)
	{
		++globvar;
		++var;
		fclose(stdout);
		exit(0);
	}
	printf("pid = %ld, glob = %d, var = %d\n",(long)getpid(),globvar,var);
	return EXIT_SUCCESS;
}
