#include <stdlib.h>
#include <pthread.h>

// 使用互斥量保护数据结构

// 用于引用计数的数据结构
struct foo {
	int             f_count;
	pthread_mutex_t f_lock;
	int             f_id;
	/* ... more stuff here ... */
};

struct foo *
foo_alloc(int id) /* allocate the object */
{
	struct foo *fp;

	if ((fp = malloc(sizeof(struct foo))) != NULL) {
		fp->f_count = 1;
		fp->f_id = id;
		// 互斥量初始化
		if (pthread_mutex_init(&fp->f_lock, NULL) != 0) {
			free(fp);
			return(NULL);
		}
		/* ... continue initialization ... */
	}
	return(fp);
}

// 引用对象加一操作
void
foo_hold(struct foo *fp) /* add a reference to the object */
{
	// 加锁
	pthread_mutex_lock(&fp->f_lock);
	fp->f_count++;
	// 解锁
	pthread_mutex_unlock(&fp->f_lock);
}

// 释放引用对象
void
foo_rele(struct foo *fp) /* release a reference to the object */
{
	//加锁
	pthread_mutex_lock(&fp->f_lock);
	// 判断引用计数是否为0
	if (--fp->f_count == 0) { /* last reference */
		pthread_mutex_unlock(&fp->f_lock);
		// 销毁互斥量
		pthread_mutex_destroy(&fp->f_lock);
		free(fp);
	} else {
		pthread_mutex_unlock(&fp->f_lock);
	}
}
