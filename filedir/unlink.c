#include "apue.h"
#include <fcntl.h>

int
main(void)
{
	// 读写方式打开文件
	if (open("tempfile", O_RDWR) < 0)
		err_sys("open error");
	// 解除符号链接
	if (unlink("tempfile") < 0)
		err_sys("unlink error");
	printf("file unlinked\n");
	sleep(15);
	printf("done\n");
	exit(0);
}
