#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void print_id()
{
	printf("uid:%d\n",getuid());
	printf("euid:%d\n",geteuid());
	printf("\n");
}
void print_res()
{
	pid_t uid,euid,suid;
	getresuid(&uid,&euid,&suid);
	printf("%d\t%d\t%d\n\n",uid,euid,suid);
}
int main(int argc,char *argv[])
{
	print_res();
	pid_t pid = geteuid();
	print_id();
	seteuid(getuid());
	print_res();
	print_id();
	setuid(pid);
	print_res();
	print_id();
	return EXIT_SUCCESS;
}
