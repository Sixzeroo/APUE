#include "apue.h"
#include <pthread.h>

// 分离状态创建线程

int
makethread(void *(*fn)(void *), void *arg)
{
	int				err;
	pthread_t		tid;
	// 线程属性数据结构
	pthread_attr_t	attr;

	err = pthread_attr_init(&attr);
	if (err != 0)
		return(err);
	// 设置线程属性
	err = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	if (err == 0)
		// 利用指定线程属性创建线程
		err = pthread_create(&tid, &attr, fn, arg);
	// 销毁线程属性
	pthread_attr_destroy(&attr);
	return(err);
}
