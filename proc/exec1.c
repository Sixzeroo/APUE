#include "apue.h"
#include <sys/wait.h>

char	*env_init[] = { "USER=unknown", "PATH=/tmp", NULL };

int
main(void)
{
	pid_t	pid;

	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) {	/* specify pathname, specify environment */
		// 使用execle执行命令，需要一个路径名和一个特定的环境
		if (execle("/home/sar/bin/echoall", "echoall", "myarg1",
				"MY ARG2", (char *)0, env_init) < 0)
			err_sys("execle error");
	}

	if (waitpid(pid, NULL, 0) < 0)
		err_sys("wait error");

	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) {	/* specify filename, inherit environment */
		// 使用execlp执行命令， 传入一个路径名
		if (execlp("echoall", "echoall", "only 1 arg", (char *)0) < 0)
			err_sys("execlp error");
	}

	exit(0);
}
