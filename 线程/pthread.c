#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

void *hello(void *arg)
{
    strcat(arg, ",Hello");
    printf("%s\n", arg);
    return NULL;
}

int main()
{
    pthread_t tid;
    char arg[256];
    strcpy(arg, "My friend");
    pthread_create(&tid, NULL, hello, (void *)arg);
    sleep(10);
    return 0;
}