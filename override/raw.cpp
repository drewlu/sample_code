#include <stdio.h>
#include "override.h"
namespace DY {
    void Hacked::show() {
        printf("raw show\n");
    }
}
