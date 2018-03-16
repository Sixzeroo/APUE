#include "apue.h"
#include <sys/wait.h>

int
main(void)
{
	pid_t	pid;
	int		status;

	// 创建子进程
	if ((pid = fork()) < 0)
		err_sys("fork error");
	// 子进程创建以后立即结束，正常终止
	else if (pid == 0)				/* child */
		exit(7);

	// 等待子进程结束
	if (wait(&status) != pid)		/* wait for child */
		err_sys("wait error");
	pr_exit(status);				/* and print its status */

	
	if ((pid = fork()) < 0)
		err_sys("fork error");
	// 异常终止子程序，使用abort()方法
	else if (pid == 0)				/* child */
		abort();					/* generates SIGABRT */

	if (wait(&status) != pid)		/* wait for child */
		err_sys("wait error");
	pr_exit(status);				/* and print its status */

	if ((pid = fork()) < 0)
		err_sys("fork error");
	// 异常终止子程序，除零方法
	else if (pid == 0)				/* child */
		status /= 0;				/* divide by 0 generates SIGFPE */

	if (wait(&status) != pid)		/* wait for child */
		err_sys("wait error");
	pr_exit(status);				/* and print its status */

	exit(0);
}
