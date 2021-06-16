#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define RETERR(str)             \
    printf("error: %s\n", str); \
    return 1

int main(int argc, char *argv[])
{
    int fd;
    char *fn;
    void *buf[BUFSIZ];
    if (argc > 1)
    {
        fn = argv[1];
    }
    fd = open(fn, O_RDONLY);

    ssize_t ret;
    while ((ret = read(fd, buf, BUFSIZ)) > 0)
    {
        printf("%s", ((char *)buf));
        memset(buf, 0, BUFSIZ);
    }
    close(fd);

    if (ret < 0)
    {
        printf("Message : %s\n", strerror(errno));
        return 1;
    }

    return 0;
}
