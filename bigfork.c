#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int main() {
    size_t memsize = 40 * 1024;
    void *p = malloc(memsize);
    if (p == NULL) {
        fprintf(stderr, "not enough memory for %d\n", memsize);
        exit(0);
    }

    pid_t pid = fork();

    if (pid == 0)
        sleep(100);
    else if (pid == -1) {
        fprintf(stderr, "failed to fork, errno:%d\n");
    } else {
        sleep(100);
    }

    return 0;
}
