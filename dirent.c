#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

#define RETERR(str)             \
    printf("error: %s\n", str); \
    return 1

int main()
{
    DIR *dp;
    dp = opendir("./");
    if (dp == NULL)
    {
        RETERR("无法打开文件夹!");
    }
    struct dirent *dir;
    while ((dir = readdir(dp)) != NULL)
    {
        struct stat s;
        lstat(dir->d_name, &s);
        printf("%lu\t%ld\t%s\n", dir->d_ino, s.st_size, dir->d_name);
    }
    size_t size = 512;
    char *ptr = malloc(size);
    if ((getcwd(ptr, size)) == NULL)
    {
        RETERR("获取当前工作目录失败!");
    }
    printf("cwd: %s\n", ptr);
    free(ptr);

    return 0;
}