#include "apue.h"
#include <pthread.h>

// 打印进程ID、新线程ID和初始线程的线程ID


// 标识线程的数据类型
pthread_t ntid;

void
printids(const char *s)
{
	pid_t		pid;
	pthread_t	tid;

	// 获取当前进程ID
	pid = getpid();
	// 获取线程ID
	tid = pthread_self();
	printf("%s pid %lu tid %lu (0x%lx)\n", s, (unsigned long)pid,
	  (unsigned long)tid, (unsigned long)tid);
}

// 新线程开始运行函数
void *
thr_fn(void *arg)
{
	printids("new thread: ");
	return((void *)0);
}

int
main(void)
{
	int		err;

	// 创建线程
	err = pthread_create(&ntid, NULL, thr_fn, NULL);
	// 不成功
	if (err != 0)
		err_exit(err, "can't create thread");
	// 打印线程ID
	printids("main thread:");
	sleep(1);
	exit(0);
}
