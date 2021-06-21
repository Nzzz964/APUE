#include "apue.h"

static void charatatime(const char *str);

int main()
{
    pid_t pid;

    TELL_WAIT();

    pid = fork();
    if (pid == 0) //child process
    {
        WAIT_PARENT();
        charatatime("output from child\n");
        charatatime("output from child\n");
        charatatime("output from child\n");
        charatatime("output from child\n");
        charatatime("output from child\n");
    }
    else if (pid > 0) //parent process
    {
        charatatime("output from parent\n");
        charatatime("output from parent\n");
        charatatime("output from parent\n");
        charatatime("output from parent\n");
        charatatime("output from parent\n");
        TELL_CHILD(pid);
    }

    exit(0);
}

static void charatatime(const char *str)
{
    const char *ptr;
    int c;

    setbuf(stdout, NULL);
    for (ptr = str; (c = *ptr++) != 0;)
    {
        putc(c, stdout);
    }
}