#include <sys/stat.h>
#include <stdio.h>

//返回错误信息
//Return error message
#define RETERR(str)             \
    printf("error: %s\n", str); \
    return 1

int main()
{
    struct stat buf;
    int err = stat("./stat.c", &buf);
    if (err < 0)
    {
        RETERR("无法打开文件");
    }
    long size = buf.st_blksize;
    printf("size: %ld\n", size);
    return 0;
}
