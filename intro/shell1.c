#include "apue.h"
#include <sys/wait.h>

int
main(void)
{
	char	buf[MAXLINE];	/* from apue.h */
	pid_t	pid;
	int		status;

	printf("%% ");	/* print prompt (printf requires %% to print %) */

	// 用标准I/O函数fgets从标准输入中读取一行
	while (fgets(buf, MAXLINE, stdin) != NULL) {
		// 因为fgets返回的每一行中都以换行符终止，但是execlp函数要求参数以null结束，所以用null替代每一行后面的换行符
		if (buf[strlen(buf) - 1] == '\n')
			buf[strlen(buf) - 1] = 0; /* replace newline with null */

		// fork创建子进程失败
		if ((pid = fork()) < 0) {
			err_sys("fork error");
			// 子进程处理：调用execlp从命令行输入读入命令，用新的程序文件替换子进程原来执行的程序文件
		} else if (pid == 0) {		/* child */
			execlp(buf, buf, (char *)0);
			err_ret("couldn't execute: %s", buf);
			exit(127);
		}

		/* parent */
		// 父进程通过waitpid等待子进程终止，指定等待的进程为参数
		if ((pid = waitpid(pid, &status, 0)) < 0)
			err_sys("waitpid error");
		printf("%% ");
	}
	exit(0);
}
