#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int makethread(void *(*fn)(void *), void *arg)
{
    int err;
    pthread_t tid;
    pthread_attr_t attr;
    err = pthread_attr_init(&attr);
    if (err != 0)
    {
        return err;
    }
    err = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    if (err == 0)
    {
        err = pthread_create(&tid, &attr, fn, arg);
    }
    pthread_attr_destroy(&attr);
    return err;
}

void *hello(void *who)
{
    char *w = (char *)who;
    printf("hello %s\n", w);
    return NULL;
}

int main()
{
    char w[512];
    strcpy(w, "Drav");
    int err = makethread(hello, (void *)w);
    printf("err = %d\n", err);
    return 0;
}