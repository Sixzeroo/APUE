#include "apue.h"

int
main(void)
{
	int		c;

	// 从标准输入获取一行输入
	while ((c = getc(stdin)) != EOF)
		// 输出一行到标准输出中
		if (putc(c, stdout) == EOF)
			err_sys("output error");

	if (ferror(stdin))
		err_sys("input error");

	exit(0);
}
