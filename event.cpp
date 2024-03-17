//
// Created by sszczyrb on 15.03.24.
//

#include "event.h"
#include "port.h"

void einit(ulong keys) {
    switch (keys) {
        case Emouse:
            port_init_mouse();
            break;
        case Ekeyboard:
        default:
            assert(!"TODO: einit unimpl keys");
    }
}


int ecanmouse() {
    return 0;
}


Mouse emouse() {
    assert(!"TODO: emouse");
    return Mouse{};
}