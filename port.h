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
struct PortPoint {
    int x;
    int y;
};
struct PortRect {
    PortPoint min;
    PortPoint max;
};
void port_image_fillpoly(PortImage dst, PortPoint *points, int size, PortImage src, PortPoint srcPoint);
void port_image_poly(PortImage dst, PortPoint *points, int size, PortImage src, PortPoint srcPoint);
void port_image_draw(PortImage dst, PortRect r, PortImage src, PortPoint p);

void port_window_update(PortImage image);

void port_sleep(long millisecs);
struct PortTm {
    int sec;
    int min;
    int hour;
};
PortTm port_localtime(long clock);

#endif //CATCLOCK_PORT_H
