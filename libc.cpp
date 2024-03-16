//
// Created by sszczyrb on 15.03.24.
//

#include "libc.h"
#include "port.h"

int fprint(int, char *, ...) {
    assert(!"TODO: fprint");
    return 0;
}

void exits(char *) {
    assert(!"TODO: exits");
}

double cos(double rad) {
    return std_cosf64(rad);
}

double sin(double rad) {
    return std_sinf64(rad);
}