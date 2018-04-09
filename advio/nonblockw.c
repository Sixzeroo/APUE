#include "apue.h"
#include <errno.h>
#include <fcntl.h>

char	buf[500000];

// 长的非阻塞write

int
main(void)
{
	int		ntowrite, nwrite;
	char	*ptr;

	// 从标准输入中读500000字节
	ntowrite = read(STDIN_FILENO, buf, sizeof(buf));
	fprintf(stderr, "read %d bytes\n", ntowrite);

	// 设置输入为非阻塞
	set_fl(STDOUT_FILENO, O_NONBLOCK);	/* set nonblocking */

	ptr = buf;
	while (ntowrite > 0) {
		errno = 0;
		// 写到标准输出中
		nwrite = write(STDOUT_FILENO, ptr, ntowrite);
		fprintf(stderr, "nwrite = %d, errno = %d\n", nwrite, errno);

		if (nwrite > 0) {
			ptr += nwrite;
			ntowrite -= nwrite;
		}
	}

	// 取消非阻塞标志
	clr_fl(STDOUT_FILENO, O_NONBLOCK);	/* clear nonblocking */

	exit(0);
}
