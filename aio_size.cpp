#include <libaio.h>
#include <stdio.h>

int main() {
    printf("sizeof(short):%d\n", sizeof(short));
    printf("sizeof(struct iocb) is %d\n", sizeof(struct iocb));
    return 0;
}
