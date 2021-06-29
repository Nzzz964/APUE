#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    pid_t pid;
    pid_t pids[3];

    pid = fork();
    if (pid == 0)
    {
        sleep(10);
        _exit(0);
    }
    pids[0] = pid;
    pid = fork();
    if (pid == 0)
    {
        sleep(20);
        exit(0);
    }
    pids[1] = pid;

    waitpid(pids[0], NULL, 0);
    pause();
}