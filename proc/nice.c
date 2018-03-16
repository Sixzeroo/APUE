#include "apue.h"
#include <errno.h>
#include <sys/time.h>

#if defined(MACOS)
#include <sys/syslimits.h>
#elif defined(SOLARIS)
#include <limits.h>
#elif defined(BSD)
#include <sys/param.h>
#endif

unsigned long long count;
struct timeval end;


// 研究nice值对进程调度的影响

void
checktime(char *str)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	// 超过时间限制以后退出
	if (tv.tv_sec >= end.tv_sec && tv.tv_usec >= end.tv_usec) {
		// 打印计数值
		printf("%s count = %lld\n", str, count);
		exit(0);
	}
}

int
main(int argc, char *argv[])
{
	pid_t	pid;
	char	*s;
	int		nzero, ret;
	int		adj = 0;

	setbuf(stdout, NULL);
#if defined(NZERO)
	nzero = NZERO;
#elif defined(_SC_NZERO)
	nzero = sysconf(_SC_NZERO);
#else
#error NZERO undefined
#endif
	printf("NZERO = %d\n", nzero);
	if (argc == 2)
		adj = strtol(argv[1], NULL, 10);
	gettimeofday(&end, NULL);
	// 限制运行的时间
	end.tv_sec += 10;	/* run for 10 seconds */

	if ((pid = fork()) < 0) {
		err_sys("fork failed");
	} else if (pid == 0) {	/* child */
		s = "child";
		// 打印子进程之前的nice值，以及调整之后的nice值
		printf("current nice value in child is %d, adjusting by %d\n",
		  nice(0)+nzero, adj);
		errno = 0;
		// 调整子进程的nice值
		if ((ret = nice(adj)) == -1 && errno != 0)
			err_sys("child set scheduling priority");
		printf("now child nice value is %d\n", ret+nzero);
	} else {		/* parent */
		s = "parent";
		printf("current nice value in parent is %d\n", nice(0)+nzero);
	}
	for(;;) {
		if (++count == 0)
			err_quit("%s counter wrap", s);
		checktime(s);
	}
}
