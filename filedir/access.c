#include "apue.h"
#include <fcntl.h>

int
main(int argc, char *argv[])
{
	// 必须输入一个参数
	if (argc != 2)
		err_quit("usage: a.out <pathname>");
	// 测试是否有读权限
	if (access(argv[1], R_OK) < 0)
		err_ret("access error for %s", argv[1]);
	else
		printf("read access OK\n");
	// 测试是否能够以只读方式打开
	if (open(argv[1], O_RDONLY) < 0)
		err_ret("open error for %s", argv[1]);
	else
		printf("open for reading OK\n");
	exit(0);
}
