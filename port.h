//
// Created by sszczyrb on 16.03.24.
//

#ifndef CATCLOCK_PORT_H
#define CATCLOCK_PORT_H

#include <cassert>

double port_cosf64(double rad);
double port_sinf64(double rad);

void port_create_window(const char* caption);
void port_init_mouse();
int port_window_width();
int port_window_height();

typedef int PortImage;
PortImage port_create_image(int width, int height);

struct PortColor {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};
void port_image_clear(PortImage image, PortColor color);
void port_image_load(PortImage image, PortColor *data, int size);

#endif //CATCLOCK_PORT_H
