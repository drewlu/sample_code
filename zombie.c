#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int main() {
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
