#include "apue.h"

int main(void)
{
	// 将文件偏移量设置为当前文件长度
	if(lseek(STDIN_FILENO, 0, SEEK_CUR) == -1)
		printf("cannot seek\n");
	else
		printf("seek OK\n");
	exit(0);
}
