#include "apue.h"

int
main(int argc, char *argv[])
{
	int		i;

	// 打印给出的命令行参数
	for (i = 0; i < argc; i++)		/* echo all command-line args */
		printf("argv[%d]: %s\n", i, argv[i]);
	exit(0);
}
