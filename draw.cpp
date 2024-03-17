//
// Created by sszczyrb on 15.03.24.
//

#include "draw.h"
#include "libc.h"
#include "port.h"

void draw(Image *dst, Rectangle r, Image *src, Image *mask, Point p) {
    assert(mask == nullptr);
    port_image_draw(dst->id, PortRect{PortPoint{r.min.x, r.min.y}, PortPoint{r.max.x, r.max.y}}, src->id,
                    PortPoint{p.x, p.y});
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
    auto r = Rect(0, 0, port_window_width(), port_window_height());
    display = new Display{
            .white = allocimage(nullptr, r, GREY1, 0, 0x1),
            .black = allocimage(nullptr, r, GREY1, 0, 0x0),
            ._isnewdisplay = 1,
    };
    screen = allocimage(display, r, RGBA32, 0, 0xFFFFFFFF);
    return 0;
}

PortColor chan_to_color(ulong chan, ulong col) {
    switch (chan) {
        case GREY1: {
            unsigned char c = (col & 1) * 255;
            return PortColor{c, c, c, 255};
        }
        case RGBA32: {
            unsigned char a = (col & 0xFF);
            unsigned char b = (col & 0xFF00) >> 8;
            unsigned char g = (col & 0xFF0000) >> 16;
            unsigned char r = (col & 0xFF000000) >> 24;
            return PortColor{r, g, b, a};
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
    int row = (r.max.x * bits + packed_colors - 1) / packed_colors - (r.min.x * bits) / packed_colors;
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

int sleep(long millisecs) {
    port_sleep(millisecs);
    return 0;
}

static Tm t = {};

Tm *localtime(long clock) {
    PortTm tm = port_localtime(clock);
    t = {
            .sec = tm.sec,
            .min = tm.min,
            .hour = tm.hour,
    };
    return &t;
}

Point ZP = {};

int flushimage(Display *d, int vis) {
    if (vis != 0) {
        port_window_update(screen->id);
    }

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

void fillpoly(Image *dst, Point *p, int np, int wind, Image *src, Point sp) {
    assert(wind == 1);
    assert(p[0].x == sp.x && p[0].y == sp.y);

    int size = np;
    PortPoint points[size];
    for (int i = 0; i < size; i++) {
        points[i] = PortPoint{p[i].x, p[i].y};
    }
    port_image_fillpoly(dst->id, reinterpret_cast<PortPoint *>(points), size, src->id, PortPoint{sp.x, sp.y});
}

void border(Image *im, Rectangle r, int _i, Image *color, Point sp) {
    for (int i = 0; i < _i; i++) { // TODO: Remove after poly() handles thickness correctly.
        Point points[5];
        points[0] = Pt(r.min.x + i, r.min.y + i);
        points[1] = Pt(r.min.x + i, r.max.y - i);
        points[2] = Pt(r.max.x - i, r.max.y - i);
        points[3] = Pt(r.max.x - i, r.min.y + i);
        points[4] = Pt(r.min.x + i, r.min.y + i);
        poly(im, points, nelem(points), 0, 0, 1, color, Pt(0, 0));
    }
}

void poly(Image *dst, Point *p, int np, int end0, int end1, int thick, Image *src, Point sp) {
    int size = np;
    PortPoint points[size];
    for (int i = 0; i < size; i++) {
        points[i] = PortPoint{p[i].x, p[i].y};
    }
    port_image_poly(dst->id, reinterpret_cast<PortPoint *>(points), size, src->id, PortPoint{sp.x, sp.y});
}
