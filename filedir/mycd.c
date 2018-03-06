#include "apue.h"

int
main(void)
{
	// 改变当前进程的工作目录
	if (chdir("/tmp") < 0)
		err_sys("chdir failed");
	printf("chdir to /tmp succeeded\n");
	exit(0);
}
