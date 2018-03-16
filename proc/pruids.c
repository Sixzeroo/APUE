#include "apue.h"

int
main(void)
{
	// 打印用户ID
	printf("real uid = %d, effective uid = %d\n", getuid(), geteuid());
	exit(0);
}
