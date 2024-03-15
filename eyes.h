//
// Created by sszczyrb on 15.03.24.
//

#ifndef CATCLOCK_EYES_H
#define CATCLOCK_EYES_H

#define eyes_width 54
#define eyes_height 23
#define eyes_x_hot -1
#define eyes_y_hot -1
static unsigned char eyes_bits[] = {
        0xff, 0x01, 0xff, 0xff, 0xfe, 0x03, 0xfc, 0xf8, 0x00, 0x3f, 0xff, 0xf0,
        0x00, 0x7c, 0xf0, 0x00, 0x1f, 0xff, 0xe0, 0x00, 0x3c, 0xe0, 0x00, 0x0f,
        0xff, 0xc0, 0x00, 0x1c, 0xc0, 0x00, 0x07, 0xff, 0x80, 0x00, 0x0c, 0x80,
        0x00, 0x03, 0xff, 0x00, 0x00, 0x04, 0x80, 0x00, 0x03, 0xff, 0x00, 0x00,
        0x04, 0x80, 0x00, 0x03, 0xff, 0x00, 0x00, 0x04, 0x00, 0x00, 0x01, 0xfe,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x01, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xfe, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x01, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xfe, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x01, 0xfe, 0x00, 0x00, 0x00, 0x80, 0x00, 0x03,
        0xff, 0x00, 0x00, 0x04, 0x80, 0x00, 0x03, 0xff, 0x00, 0x00, 0x04, 0x80,
        0x00, 0x03, 0xff, 0x00, 0x00, 0x04, 0xc0, 0x00, 0x07, 0xff, 0x80, 0x00,
        0x0c, 0xe0, 0x00, 0x0f, 0xff, 0xc0, 0x00, 0x1c, 0xf0, 0x00, 0x1f, 0xff,
        0xe0, 0x00, 0x3c, 0xf8, 0x00, 0x3f, 0x57, 0xf0, 0x00, 0x7c, 0xff, 0x01,
        0xfe, 0xab, 0xfe, 0x03, 0xfc
};

#endif //CATCLOCK_EYES_H
