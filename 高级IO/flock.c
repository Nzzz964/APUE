#include <fcntl.h>
#include <stdio.h>

//🔒 文件记录锁
// struct flock lock;

struct test_a //size = 16
{
    int a;
    short b;
    long c;
};

struct test_b //size = 24
{
    int a;
    long c;
    short b;
};

int main()
{
    struct test_a test_a;
    struct test_b test_b;
    printf("sizeof struct test_a = %lu\n", sizeof(test_a));
    printf("sizeof struct test_b = %lu\n", sizeof(test_b));
}