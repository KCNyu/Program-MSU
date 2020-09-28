#include "sys/syscall.h"
#include <stdio.h>
int getchar(void)
{
    char c;
    return (read(0,&c,1)==1)?(unsigned char)c:EOF
    //EOF定义在stdio.h文件中
}
