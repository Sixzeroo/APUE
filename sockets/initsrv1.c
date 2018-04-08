#include "apue.h"
#include <errno.h>
#include <sys/socket.h>

// 分配和初始化套接字供服务器进程使用

int
initserver(int type, const struct sockaddr *addr, socklen_t alen,
  int qlen)
{
	int fd;
	int err = 0;

	// 创建套接字
	if ((fd = socket(addr->sa_family, type, 0)) < 0)
		return(-1);
	// 将套接字和地址关联
	if (bind(fd, addr, alen) < 0)
		goto errout;
	if (type == SOCK_STREAM || type == SOCK_SEQPACKET) {
		// 监听端口
		if (listen(fd, qlen) < 0)
			goto errout;
	}
	return(fd);

errout:
	err = errno;
	close(fd);
	errno = err;
	return(-1);
}
