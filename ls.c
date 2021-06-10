#include <dirent.h>
#include <stdio.h>
#include <stddef.h>

int main(int argc, char *argv[])
{
    DIR *dp;
    struct dirent *dirp;

    if (argc != 2)
    {
        return 1;
    }
    if ((dp = opendir(argv[1])) == NULL)
    {
        return 2;
    }
    while ((dirp = readdir(dp)) != NULL)
    {
        printf("%s\n", dirp->d_name);
    }
    return 0;
}
