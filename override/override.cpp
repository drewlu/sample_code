#define _GNU_SOURCE 1
#include "override.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dlfcn.h>

namespace DY {

    void Hacked::show() {
        printf("hacked show\n");
    }
    void WrapperHacked::show() {
        printf("hacked show\n");
    }
    void WrapperHacked::show2() {
        printf("hacked show\n");
    }
}
