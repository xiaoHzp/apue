#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
	int			i;
	extern char	**environ;

	for(i = 0;i<argc;i++)
		printf("argv[%d]:%s\n",i,argv[i]);
	for(i = 0;i<3;i++)
		printf("%s\n",environ[i]);
	return EXIT_SUCCESS;
}
