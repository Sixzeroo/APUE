#include "apue.h"

int
main(void)
{
	char	*ptr;
	size_t		size;

	// 改变工作目录
	if (chdir("/usr/spool/uucppublic") < 0)
		err_sys("chdir failed");

	ptr = path_alloc(&size);	/* our own function */
	// 获取当前工作目录的绝对路径
	if (getcwd(ptr, size) == NULL)
		err_sys("getcwd failed");

	printf("cwd = %s\n", ptr);
	exit(0);
}
