#include <unistd.h>
#include <sys/wait.h>
#include <iostream>

int globalVar = 6;
char buf[] = "a write to stdout\n";

int main()
{
    //                        防止输出\0终止符
    write(STDOUT_FILENO, buf, sizeof(buf) - 1);
    //获取进程ID
    __pid_t pid = getpid();
    //调用进程的父进程ID
    __pid_t ppid = getppid();
    printf("pid: %d\tppid: %d\n", pid, ppid);
    //获取进程实际用户ID
    __uid_t uid = getuid();
    //获取进程实际组ID
    __gid_t gid = getgid();
    printf("uid: %d\tgid: %d\n", uid, gid);

    int var = 88;

    __pid_t n_pid = fork();
    if (n_pid == 0) //子进程返回0
    {
        globalVar++;
        var++;
    }
    else if (n_pid > 0) //父进程返回子进程ID
    {
        //等待子进程 阻塞
        __pid_t w_pid = wait(NULL);
        printf("w_pid: %d\n", w_pid);
    }
    printf("pid=%d,glob=%d,var=%d\n", getpid(), globalVar, var);

    return 0;
}