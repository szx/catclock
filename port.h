//
// Created by sszczyrb on 16.03.24.
//

#ifndef CATCLOCK_PORT_H
#define CATCLOCK_PORT_H

#include <cassert>

double port_cosf64(double rad);
double port_sinf64(double rad);

struct PortWindow {
    void *handle;
};
static PortWindow port_display = {};

void port_create_window(const char* caption);

#endif //CATCLOCK_PORT_H
