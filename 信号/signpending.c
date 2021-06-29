#include "apue.h"

void sig_int(int);

int main()
{
    sigset_t newmask, oldmask, pendmask;
    if (signal(SIGINT, sig_int) == SIG_ERR)
    {
        err_sys("can't catch SIGINT");
    }
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGINT);

    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
    {
        err_sys("SIG_BLOCK error");
    }

    sleep(5);
    if (sigpending(&pendmask) < 0)
    {
        err_sys("sigpending error");
    }
    if (sigismember(&pendmask, SIGINT))
    {
        printf("\nSIGINT pending\n");
    }
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
    {
        err_sys("SIG_SETMASK error");
    }
    printf("SIGINT unblocked\n");
    sleep(5);
    return 0;
}

void sig_int(int signo)
{
    printf("catch SIGINT\n");
    if (signal(SIGINT, SIG_DFL) == SIG_ERR)
    {
        err_sys("can't reset SIGINT");
    }
}