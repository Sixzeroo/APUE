#include <limits.h>
#include <string.h>

#define MAXSTRINGSZ	4096

// 一个不可重入版本的getenv的实现

static char envbuf[MAXSTRINGSZ];

extern char **environ;

char *
getenv(const char *name)
{
	int i, len;

	len = strlen(name);
	for (i = 0; environ[i] != NULL; i++) {
		// 获取指定的变量并发挥字符数组
		if ((strncmp(name, environ[i], len) == 0) &&
		  (environ[i][len] == '=')) {
			strncpy(envbuf, &environ[i][len+1], MAXSTRINGSZ-1);
			return(envbuf);
		}
	}
	return(NULL);
}
