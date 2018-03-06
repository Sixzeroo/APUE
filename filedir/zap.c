#include "apue.h"
#include <fcntl.h>

int
main(int argc, char *argv[])
{
	int				i, fd;
	struct stat		statbuf;
	struct timespec	times[2];

	for (i = 1; i < argc; i++) {
		// 获取修改之前的文件信息
		if (stat(argv[i], &statbuf) < 0) {	/* fetch current times */
			err_ret("%s: stat error", argv[i]);
			continue;
		}
		// 使用open 将文件长度截断为0
		if ((fd = open(argv[i], O_RDWR | O_TRUNC)) < 0) { /* truncate */
			err_ret("%s: open error", argv[i]);
			continue;
		}
		// 重新设置时间信息为之前的值
		times[0] = statbuf.st_atim;
		times[1] = statbuf.st_mtim;
		if (futimens(fd, times) < 0)		/* reset times */
			err_ret("%s: futimens error", argv[i]);
		close(fd);
	}
	exit(0);
}
