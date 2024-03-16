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
    display = new Display {
        ._isnewdisplay = 1
    };
    return 0;
}

Image *allocimage(Display *d, Rectangle r, ulong chan, int repl, ulong val) {
    auto *i = new Image{};
    assert(!"TODO: allocimage");
    return i;
}

int loadimage(Image *i, Rectangle r, uchar *data, int ndata) {
    assert(!"TODO: loadimage");
    return 0;
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
    return Point {
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
