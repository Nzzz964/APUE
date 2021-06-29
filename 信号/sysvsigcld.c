#include <sys/wait.h>
#include "apue.h"

//此程序不能再某些传统的 SystemV 平台上正常工作。程序一行行地重复输出 "SIGCLD received" 最后进程用完其栈空间并异常终止
//所以 SIGCLD 原来在 SystemV 系统上的意思是 如果有需要等待的子进程就调用 SIGCLD 的 handler 不是子进程终止时调用 ?
static void sig_cld(int);

int main()
{
    pid_t pid;
    if (signal(SIGCLD, sig_cld) == SIG_ERR)
    {
        perror("signal error");
    }
    if ((pid = fork()) < 0)
    {
        perror("fork error");
    }
    else if (pid == 0) /* child process */
    {
        printf("pid = %d\n", getpid());
        sleep(2);
        _exit(0);
    }
    pause();
    exit(0);
}

//信号处理函数
static void sig_cld(int signo)
{
    pid_t pid;
    int status;
    printf("SIGCLD received\n");
    if (signal(SIGCLD, sig_cld) == SIG_ERR)
    {
        perror("signal error");
    }
    if ((pid = wait(&status)) < 0)
    {
        perror("wait error");
    }
    printf("pid = %d\n", pid);
}