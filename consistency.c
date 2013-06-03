#include <pthread.h>
#include <assert.h>

int a, b;

void *foo(void *none) {
    a = 1;
    b = 1;
}

void *bar(void *none) {
    while (b == 0) continue;
    assert(a == 1);
}

int main() {
    pthread_t threads[2];
    pthread_attr_t attrs[2];

    pthread_attr_init(&attrs[0]);
    pthread_attr_init(&attrs[1]);

    pthread_create(&threads[0], &attrs[0], foo, NULL);
    pthread_create(&threads[1], &attrs[1], bar, NULL);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    return 0;
}
