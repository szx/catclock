//
// Created by sszczyrb on 15.03.24.
//

#include "draw.h"
#include "libc.h"


void draw(Image *, Rectangle, Image *, Image *, Point) {
    // TODO: Implement draw.
}

Display *display;
Font *font;
Image *screen;
Screen *_screen;
int _cursorfd;
int _drawdebug;    /* set to 1 to see errors from flushimage */

int initdraw(void (*error)(Display *, char *), char *fontname, char *label) {
    // TODO: initdraw
    return 0;
}

Image *allocimage(Display *d, Rectangle r, ulong chan, int repl, ulong val) {
    auto *i = new Image{};
    return i;
}

int loadimage(Image *i, Rectangle r, uchar *data, int ndata) {
    // TODO: loadimage
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
    // TODO: getwindow
    return 0;
}

char *argv0 = nullptr;

int chartorune(Rune *, char *) {
    // TODO: chartorune
    return 0;
}

int sleep(long) {
    // TODO:
    return 0;
}

Tm *localtime(long) {
    // TODO:
    return nullptr;
}

Point ZP = {};

int flushimage(Display *, int) {
    // TODO:
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
    // TODO:
}

void border(Image *, Rectangle, int, Image *, Point) {
    // TODO:
}

void poly(Image *, Point *, int, int, int, int, Image *, Point) {
    // TODO:
}
