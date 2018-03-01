#include "apue.h"

#define	BUFFSIZE	4096

int
main(void)
{
	int		n;
	char	buf[BUFFSIZE];

	// STDIN_FILENO 和 STDOUT_FILENO指定标准输入输出的文件描述符 在POSIX标准，他们分别是0和1
	// read函数返回读取的字节数，此值作为写入的字节数传入write函数中
	while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
		if (write(STDOUT_FILENO, buf, n) != n)
			err_sys("write error");

	if (n < 0)
		err_sys("read error");

	exit(0);
}
