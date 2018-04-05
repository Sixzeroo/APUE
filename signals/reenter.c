#include "apue.h"
#include <pwd.h>

// 信号处理函数
static void
my_alarm(int signo)
{
	struct passwd	*rootptr;

	printf("in signal handler\n");
	// 使用非可重入函数getpwnam
	if ((rootptr = getpwnam("root")) == NULL)
			err_sys("getpwnam(root) error");
	alarm(1);
}

int
main(void)
{
	struct passwd	*ptr;

	// 捕捉SIGALRM信号
	signal(SIGALRM, my_alarm);
	alarm(1);
	for ( ; ; ) {
		if ((ptr = getpwnam("sar")) == NULL)
			err_sys("getpwnam error");
		if (strcmp(ptr->pw_name, "sar") != 0)
			printf("return value corrupted!, pw_name = %s\n",
					ptr->pw_name);
	}
}
