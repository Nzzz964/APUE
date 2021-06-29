#include "apue.h"
#include <errno.h>

//打印调用进程信号屏蔽字中的信号名称
void pr_mask(const char *str)
{
    sigset_t sigset;
    int errno_save;

    errno_save = errno;
    //sigprocmask 可以检测和更改 或同时进行检测和更改进程的信号屏蔽字
    if (sigprocmask(0, NULL, &sigset) < 0)
    {
        err_ret("sigprocmask error");
    }
    else
    {
        printf("%s", str);
        if (sigismember(&sigset, SIGINT)) //检测SIGINT是否是sigset的成员
        {
            printf(" SIGINT");
        }
        if (sigismember(&sigset, SIGQUIT))
        {
            printf(" SIGQUIT");
        }
        if (sigismember(&sigset, SIGUSR1))
        {
            printf(" SIGUSR1");
        }
        if (sigismember(&sigset, SIGALRM))
        {
            printf(" SIGALRM");
        }
    }

    printf("\n");
}

int main()
{
    pr_mask("main: ");
    return 0;
}