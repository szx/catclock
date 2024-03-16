//
// Created by sszczyrb on 15.03.24.
//

#include "draw.h"
#include "libc.h"
#include "port.h"

void draw(Image *, Rectangle, Image *, Image *, Point) {
    assert(!"TODO: draw");
}

Display *display;
Font *font;
Image *screen;
Screen *_screen;
int _cursorfd;
int _drawdebug;    /* set to 1 to see errors from flushimage */

int initdraw(void (*error)(Display *, char *), char *fontname, char *label) {
    assert(error == nullptr);
    assert(fontname == nullptr);
    port_create_window(label);
    display = new Display{
            ._isnewdisplay = 1
    };
    screen = new Image{
            .display = display,
            .id = 0,
            .r = Rect(0, 0, port_window_width(), port_window_height()),
            .clipr = Rect(0, 0, port_window_width(), port_window_height()),
            .depth = 32,
            .chan = RGBA32,
            .repl = 0,
            .screen = nullptr, // TODO: Should not be null?
            .next = nullptr,
    };
    return 0;
}

PortColor chan_to_color(ulong chan, ulong col) {
    switch (chan) {
        case GREY1: {
            unsigned char c = (col & 1) * 255;
            return PortColor{c, c, c, 255};
        }
        default:
            assert(!"TODO: chan_to_color unimpl");
    }
    return PortColor{0, 0, 0, 0};
}

Image *allocimage(Display *d, Rectangle r, ulong chan, int repl, ulong val) {
    PortImage image = port_create_image(r.max.x - r.min.x, r.max.y - r.min.y);
    port_image_clear(image, chan_to_color(chan, val));
    auto *i = new Image{
            .display = d,
            .id = image,
            .r = r,
            .clipr = r,
            .depth = 32,
            .chan = chan,
            .repl = repl,
            .screen = nullptr,
            .next = nullptr,
    };
    return i;
}

int loadimage(Image *i, Rectangle r, uchar *data, int ndata) {
    assert(r.min.x == 0);
    assert(r.min.y == 0);
    assert(r.max.x == i->r.max.x);
    assert(r.max.y == i->r.max.y);

    int width = r.max.x;
    int height = r.max.y;
    int size = width * height;
    auto c = new PortColor[size];
    int bits = NBITS(i->chan);
    int packed_colors = sizeof(uchar) * 8 / bits;
    int row = (r.max.x*bits+packed_colors-1)/packed_colors - (r.min.x*bits)/packed_colors;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int data_index = (y * row) + x / packed_colors;
            int offset_index = (packed_colors - 1) - (x) % packed_colors;
            c[y * width + x] = chan_to_color(i->chan, data[data_index] >> offset_index);
        }
    }

    port_image_load(i->id, c, size);
    return ndata;
}

Rectangle Rect(int x, int y, int bx, int by) {
    Rectangle r;

    r.min.x = x;
    r.min.y = y;
    r.max.x = bx;
    r.max.y = by;
    return r;
}

int ptinrect(Point p, Rectangle r) {
    return p.x >= r.min.x && p.x <= r.max.x && p.y >= r.min.y && p.y <= r.max.y;
}

int getwindow(Display *d, int ref) {
    assert(!"TODO: getwindow");
    return 0;
}

char *argv0 = nullptr;

int chartorune(Rune *, char *) {
    assert(!"TODO: chartorune");
    return 0;
}

int sleep(long) {
    assert(!"TODO: sleep");
    return 0;
}

Tm *localtime(long) {
    assert(!"TODO: localtime");
    return nullptr;
}

Point ZP = {};

int flushimage(Display *, int) {
    assert(!"TODO: flushimage");
    return 0;
}

Point Pt(int x, int y) {
    return Point{x, y};
}

Point addpt(Point p1, Point p2) {
    return Point{
            .x = p1.x + p2.x,
            .y = p1.y + p2.y
    };
}

Point mulpt(Point p, int scalar) {
    return Point{
            .x = p.x * scalar,
            .y = p.y * scalar,
    };
}

void fillpoly(Image *, Point *, int, int, Image *, Point) {
    assert(!"TODO: fillpoly");
}

void border(Image *, Rectangle, int, Image *, Point) {
    assert(!"TODO: border");
}

void poly(Image *, Point *, int, int, int, int, Image *, Point) {
    assert(!"TODO: poly");
}
