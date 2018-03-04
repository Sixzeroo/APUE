#include "apue.h"
#include <fcntl.h>

char	buf1[] = "abcdefghij";
char	buf2[] = "ABCDEFGHIJ";

int
main(void)
{
	int		fd;

	// 创建文件
	if ((fd = creat("file.hole", FILE_MODE)) < 0)
		err_sys("creat error");

	// 写入a-j，此时文件偏移量为10
	if (write(fd, buf1, 10) != 10)
		err_sys("buf1 write error");
	/* offset now = 10 */

	// 改变文件偏移量到16384
	if (lseek(fd, 16384, SEEK_SET) == -1)
		err_sys("lseek error");
	/* offset now = 16384 */

	// 在新的文件偏移量下写入A-J
	if (write(fd, buf2, 10) != 10)
		err_sys("buf2 write error");
	/* offset now = 16394 */

	exit(0);
}
