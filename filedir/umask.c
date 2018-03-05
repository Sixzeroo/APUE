#include "apue.h"
#include <fcntl.h>

#define RWRWRW (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

int
main(void)
{
	// 修改文件模式创建屏蔽字，不做任何屏蔽
	umask(0);
	if (creat("foo", RWRWRW) < 0)
		err_sys("creat error for foo");
	// 再次修改文件模式创建屏蔽字，屏蔽组成员读写、其他用户读写
	umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if (creat("bar", RWRWRW) < 0)
		err_sys("creat error for bar");
	exit(0);
}
