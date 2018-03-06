#include "apue.h"

int
main(void)
{
	// 保存文件信息的数据结构
	struct stat		statbuf;

	/* turn on set-group-ID and turn off group-execute */

	// 获取文件信息
	if (stat("foo", &statbuf) < 0)
		err_sys("stat error for foo");
	// 关闭组执行、打开设置组ID位
	if (chmod("foo", (statbuf.st_mode & ~S_IXGRP) | S_ISGID) < 0)
		err_sys("chmod error for foo");

	/* set absolute mode to "rw-r--r--" */

	// 设置权限位为 rw-r--r--
	if (chmod("bar", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) < 0)
		err_sys("chmod error for bar");

	exit(0);
}
