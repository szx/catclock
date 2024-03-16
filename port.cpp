//
// Created by sszczyrb on 16.03.24.
//

#include "port.h"
#include <cmath>
#include <SFML/Graphics.hpp>

double port_cosf64(double rad) {
    return cosf64(rad);
}

double port_sinf64(double rad) {
    return sinf64(rad);
}

void port_create_window(const char *caption) {
    auto window = new sf::RenderWindow(sf::VideoMode(800, 600), caption);
    port_display = PortWindow{.handle = window};
}
