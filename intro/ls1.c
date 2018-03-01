#include "apue.h"  //用于本书各个实例 包含某些标准头文件，定义了很多常量和函数模型
#include <dirent.h> // 使用opendir和readdir的函数原型，以及dirent结构的定义

int
main(int argc, char *argv[])
{
	DIR				*dp;
	struct dirent	*dirp;

	// 给出的参数不符
	if (argc != 2)
		err_quit("usage: ls directory_name");
	// 获取命令行的第一个参数，	打开目录，返回一个DIR结构指针
	if ((dp = opendir(argv[1])) == NULL)
		err_sys("can't open %s", argv[1]);
	// 读取目录并输出目录名
	while ((dirp = readdir(dp)) != NULL)
		printf("%s\n", dirp->d_name);
	// 关闭目录
	closedir(dp);
	exit(0);
}
