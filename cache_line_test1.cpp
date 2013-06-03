#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

struct DATA 
{
    int a;
    int b;
};

int main() {
    struct timeval t0, t1;
    DATA * pMyData = (DATA *)malloc(sizeof(struct DATA)*10*1024*1024);

    gettimeofday(&t0, NULL);

    for (long i=0; i<10*1024*1024; i++)
    {
        pMyData[i].a = pMyData[i].b;
    }

    gettimeofday(&t1, NULL);
    printf("usecs:%lu\n", (t1.tv_sec-t0.tv_sec)*1000000+(t1.tv_usec-t0.tv_usec));

    free(pMyData);
}
