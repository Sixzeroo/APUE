#include "apue.h"

int
main(void)
{
	char	buf[MAXLINE];

	// 从标准输入流中读取一行
	while (fgets(buf, MAXLINE, stdin) != NULL)
		// 输出一行到标准输出流
		if (fputs(buf, stdout) == EOF)
			err_sys("output error");

	if (ferror(stdin))
		err_sys("input error");

	exit(0);
}
