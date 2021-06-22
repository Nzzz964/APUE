#include "apue.h"

int main()
{
    pid_t c_pid;

    c_pid = fork();
    if (c_pid == 0)
    {
        char *const argv[] = {"echo", "executed by execv", NULL};
        execv("/usr/bin/echo", argv);
    }
    //更改用户ID和组ID
    if(setuid(0) < 0){
        err_sys("setuid");
    }
    exit(0);
}