#include "apue.h"
#include <pthread.h>

// 使用pthread_mutex_timedlock避免永久阻塞

int
main(void)
{
	int err;
	struct timespec tout;
	struct tm *tmp;
	char buf[64];
	pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

	// 对互斥量及逆行锁定
	pthread_mutex_lock(&lock);
	printf("mutex is locked\n");
	// 获取时间
	clock_gettime(CLOCK_REALTIME, &tout);
	tmp = localtime(&tout.tv_sec);
	strftime(buf, sizeof(buf), "%r", tmp);
	printf("current time is %s\n", buf);
	// 等待的绝对时间
	tout.tv_sec += 10;	/* 10 seconds from now */
	/* caution: this could lead to deadlock */
	// 设定lock愿意等待阻塞的时间
	err = pthread_mutex_timedlock(&lock, &tout);
	// 等待以后的情况
	clock_gettime(CLOCK_REALTIME, &tout);
	tmp = localtime(&tout.tv_sec);
	strftime(buf, sizeof(buf), "%r", tmp);
	printf("the time is now %s\n", buf);
	if (err == 0)
		printf("mutex locked again!\n");
	else
		printf("can't lock mutex again: %s\n", strerror(err));
	exit(0);
}
