#include <unistd.h>

int main() {
    int err;
    err = rmdir("./test");
    return err;
}
