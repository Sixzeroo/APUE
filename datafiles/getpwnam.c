#include <pwd.h>
#include <stddef.h>
#include <string.h>

struct passwd *
getpwnam(const char *name)
{
    struct passwd  *ptr;

	// 反绕所使用的文件
    setpwent();
	// 获得一个passwd结构
    while ((ptr = getpwent()) != NULL)
        if (strcmp(name, ptr->pw_name) == 0)
            break;		/* found a match */
	// 关闭这些文件
    endpwent();
    return(ptr);	/* ptr is NULL if no match found */
}
