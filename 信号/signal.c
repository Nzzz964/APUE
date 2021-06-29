#include "apue.h"

//信号处理函数
static void sig_usr(int);

int main()
{
    if (signal(SIGUSR1, sig_usr) == SIG_ERR)
    {
        err_sys("can't catch SIGUSR1");
    }
    if (signal(SIGUSR2, sig_usr) == SIG_ERR)
    {
        err_sys("can't catch SIGUSR2");
    }
    if (signal(SIGINT, sig_usr) == SIG_ERR)
    {
        err_sys("can't catch SIGINT");
    }
    for (;;)
    {
        pause();
    }
}

static void sig_usr(int signo) //信号类型
{
    if (signo == SIGUSR1)
    {
        printf("received SIGUSR1\n");
    }
    else if (signo == SIGUSR2)
    {
        printf("received SIGUSR2\n");
    }
    else if (signo == SIGINT)
    {
        printf("received SIGINT\n");
    }
    else
    {
        err_dump("received signal %d\n", signo);
    }
}