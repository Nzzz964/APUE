#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//返回错误
#define RETERR(str)             \
    printf("error: %s\n", str); \
    return 1

static void my_exit(void)
{
    printf("My exit func\n");
}

int main(int argc, char *argv, char *envp[])
{
    FILE *f = fopen("./buf.c", "r");
    //返回Unicode码
    int ret;
    while ((ret = getc(f)) != EOF)
    {
        putc(ret, stdout);
    }
    printf("\n");
    //重置偏移量
    fseek(f, 0, SEEK_SET);

    //一次读取一行
    char buf[BUFSIZ];
    fgets(buf, BUFSIZ, f);
    fputs(buf, stdout);
    fclose(f);

    printf("\n");
    //打印环境变量
    for (int i = 0; envp[i] != NULL; i++)
    {
        printf("%s\n", envp[i]);
    }
    //注册终止处理程序
    atexit(my_exit);
    return 0;
}
