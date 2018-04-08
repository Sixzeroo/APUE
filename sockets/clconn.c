#include "apue.h"
#include <sys/socket.h>

#define MAXSLEEP 128

// 采用指数补偿算法，重连

int
connect_retry(int sockfd, const struct sockaddr *addr, socklen_t alen)
{
	int numsec;

	/*
	 * Try to connect with exponential backoff.
	 */
	for (numsec = 1; numsec <= MAXSLEEP; numsec <<= 1) {
		// 进行重连
		if (connect(sockfd, addr, alen) == 0) {
			/*
			 * Connection accepted.
			 */
			return(0);
		}

		/*
		 * Delay before trying again.
		 */
		// 每次休眠时间呈指数级增大
		if (numsec <= MAXSLEEP/2)
			sleep(numsec);
	}
	return(-1);
}
