#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/times.h>

static void pr_time(clock_t,struct tms*,struct tms*);
static void do_cmd(char*);

int main(int argc,char *argv[])
{
	int i;
	setbuf(stdout,NULL);
	for(i = 1;i < argc;i++)
		do_cmd(argv[i]);
	return EXIT_SUCCESS;
}

static void do_cmd(char *cmd)
{
	struct tms tmsstart,tmsend;
	clock_t start,end;
	int status;

	printf("\ncommand: %s\n",cmd);
	if((start = times(&tmsstart))== -1)
		return ;
	if(system(cmd) < 0)
		return ;
	if((end = times(&tmsend)) == -1)
		return ;
	pr_time(end - start,&tmsstart,&tmsend);
}

static void pr_time(clock_t real,struct tms *tmsstart,struct tms *tmsend)
{
	static long clktck = 0;
	if(clktck == 0)
		if((clktck = sysconf(_SC_CLK_TCK)) < 0)
			return;

	printf("real: %7.2f\n", real/(double)clktck);
	printf("user: %7.2f\n", (tmsend->tms_utime - tmsstart->tms_utime) / (double)clktck);
	printf("system: %7.2f\n",(tmsend->tms_stime - tmsstart->tms_stime) / (double)clktck);
	printf("child user: %7.2f\n",(tmsend->tms_cutime - tmsstart->tms_cutime) / (double)clktck);
	printf("child system: %7.2f\n",(tmsend->tms_cstime - tmsstart->tms_cstime) / (double)clktck);
}
