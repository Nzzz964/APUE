#include "apue.h"
#include <pthread.h>

struct msg
{
    char const *m_msg;
    struct msg *m_next;
};

typedef struct msg msg;

msg *workq;

pthread_cond_t q_ready = PTHREAD_COND_INITIALIZER;
pthread_mutex_t q_lock = PTHREAD_MUTEX_INITIALIZER;

void process_msg(void)
{
    msg *mp;
    for (;;)
    {
        pthread_mutex_lock(&q_lock);
        while (workq == NULL)
        {
            pthread_cond_wait(&q_ready, &q_lock);
        }
        printf("%s\n", workq->m_msg);
        mp = workq;
        workq = mp->m_next;
        pthread_mutex_unlock(&q_lock);
    }
}

void enqueue_msg(msg *mp)
{
    pthread_mutex_lock(&q_lock);
    mp->m_next = workq;
    workq = mp;
    pthread_mutex_unlock(&q_lock);
    pthread_cond_signal(&q_ready);
}

void sig_usr1(int signo)
{
    msg mp;
    mp.m_msg = "Hello World";
    enqueue_msg(&mp);
    if (signal(SIGUSR1, sig_usr1) == SIG_ERR)
    {
        err_sys("SIGUSR1 ERROR");
    }
}

int main()
{
    printf("pid = %d\n", getpid());
    if (signal(SIGUSR1, sig_usr1) == SIG_ERR)
    {
        err_sys("SIGUSR1 ERROR");
    }
    process_msg();
    return 0;
}