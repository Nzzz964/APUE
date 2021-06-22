#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define ERR(s)     \
    printf("s\n"); \
    exit(0)

int main()
{
    pid_t pid;

    printf("main process, pid = %d\n", getpid());

    pid = fork();
    if (pid == 0)
    {
        printf("first child pid = %d , parent pid = %d\n", getpid(), getppid());
        pid = fork();
        //第二个子进程被init接管
        if (pid == 0)
        {
            sleep(2);
            printf("\rsecond child pid = %d , parent pid = %d", getpid(), getppid());
            exit(0);
        }
        exit(0);
    }

    //wait for first child
    if (waitpid(pid, NULL, 0) != pid)
    {
        ERR("wait pid error");
    }

    exit(0);
}