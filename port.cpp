//
// Created by sszczyrb on 16.03.24.
//

#include "port.h"
#include <cmath>
#include <SFML/Graphics.hpp>
#include <vector>

double port_cosf64(double rad) {
    return cosf64(rad);
}

double port_sinf64(double rad) {
    return sinf64(rad);
}

static sf::RenderWindow *port_display = {};
static bool use_mouse = false;

void port_create_window(const char *caption) {
    port_display = new sf::RenderWindow(sf::VideoMode(800, 600), caption);
}

void port_init_mouse() {
    use_mouse = true;
}

int port_window_width() {
    return port_display->getSize().x;
}

int port_window_height() {
    return port_display->getSize().y;
}

static std::vector<sf::Texture> images;

PortImage port_create_image(int width, int height) {
    auto image = sf::Texture();
    image.create(width, height);
    images.push_back(image);
    return (int) images.size() - 1;
}

void debug_sfml_texture(sf::Texture texture) {
    sf::Sprite sprite;
    sprite.setTexture(texture);
    while (true) {
        port_display->clear();
        port_display->draw(sprite);
        port_display->display();
    }
}

static std::vector<uint32_t> rgbaData;

uint32_t color_to_rgba(PortColor c) {
    return c.a << 24 | c.b << 16 | c.g << 8 | c.r; // little endian
}

void port_image_clear(PortImage _image, PortColor color) {
    auto image = images[_image];
    unsigned int width = image.getSize().x;
    unsigned int height = image.getSize().y;
    rgbaData.resize(width * height);
    std::fill(rgbaData.begin(), rgbaData.end(), color_to_rgba(color));
    sf::Image imageData;
    imageData.create(width, height, reinterpret_cast<const sf::Uint8 *>(rgbaData.data()));
    image.loadFromImage(imageData);
}

void port_image_load(PortImage _image, PortColor *data, int size) {
    auto image = images[_image];
    rgbaData.resize(size);
    for (int i = 0; i < size; i++) {
        auto c = color_to_rgba(data[i]);
        rgbaData[i] = c;
    }
    sf::Image imageData;
    imageData.create(image.getSize().x, image.getSize().y, reinterpret_cast<const sf::Uint8 *>(rgbaData.data()));
    image.loadFromImage(imageData);
}
