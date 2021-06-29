#include <sys/wait.h>
#include <sys/times.h>
#include <sys/resource.h>
#include "apue.h"

clock_t times(struct tms *buf);

int main()
{
    pid_t c_pid;

    c_pid = fork();
    if (c_pid == 0)
    {
        char *const argv[] = {"echo", "executed by execv", NULL};
        execv("/usr/bin/echo", argv);
    }
    if (waitpid(c_pid, NULL, 0) != c_pid)
    {
        err_sys("waitpid");
    }
    //更改实际和有效用户ID和组ID
    if (setuid(1000) < 0)
    {
        err_sys("setuid");
    }
    if (setgid(1000) < 0)
    {
        err_sys("setgid");
    }
    //修改有效用户ID和组ID
    seteuid(1000);
    setegid(1000);

    //函数system
    //system函数实现了 fork exec 和 waitpid
    system("date");

    //用户标识 获取登录用户名
    printf("%s\n", getlogin());

    //nice 函数修改进程调度优先级 nice越小优先级越高
    nice(99);
    //获取一组相关进程的nice值
    //getpriority();

    //进程时间 查看进程子进程进程时间
    struct tms buf;
    clock_t clock = times(&buf);
    printf("cpu tck: %d , system cpu time: %d , system user time: %d\n", clock, buf.tms_stime, buf.tms_utime);
    long clktck = sysconf(_SC_CLK_TCK);
    printf("cpu tck: %d\n", clock / (double)clktck);
    exit(0);
}