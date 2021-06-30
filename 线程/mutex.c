#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <stddef.h>
#include <signal.h>

struct foo
{
    int f_count;
    pthread_mutex_t f_lock;
    int f_id;
};

struct foo *foo_alloc(int id)
{
    struct foo *fp;
    fp = (struct foo *)malloc(sizeof(struct foo));
    if (fp != NULL)
    {
        fp->f_count = 1;
        fp->f_id = id;
        if (pthread_mutex_init(&fp->f_lock, NULL) != 0)
        {
            //mutex init 错误
            free(fp);
            return NULL;
        }
    }
    return fp;
}

void foo_print(struct foo *fp)
{
    printf("foo_print: %d\n", fp->f_count);
}

void foo_hold(struct foo *fp)
{
    pthread_mutex_lock(&fp->f_lock);
    fp->f_count++;
    pthread_mutex_unlock(&fp->f_lock);
}

void foo_release(struct foo *fp)
{
    pthread_mutex_lock(&fp->f_lock);
    if (--fp->f_count == 0)
    {
        pthread_mutex_unlock(&fp->f_lock);
        pthread_mutex_destroy(&fp->f_lock);
        free(fp);
    }
    else
    {
        pthread_mutex_unlock(&fp->f_lock);
    }
}

int main()
{
    struct foo *f;
    f = foo_alloc(1);
    foo_hold(f);
    foo_print(f);
    // pthread_mutex_lock(&f->f_lock); //lock两次 死锁
    sleep(3);
    // pthread_mutex_unlock(&f->f_lock);
    foo_hold(f);
    foo_print(f);
    // pthread_mutex_unlock(&f->f_lock);
    foo_release(f);
    foo_print(f);
}