#include <stdlib.h>
using namespace std;

int main() {
    void *p = malloc(128);
    free(p);
    return 0;
}
