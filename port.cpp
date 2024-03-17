//
// Created by sszczyrb on 16.03.24.
//

#include "port.h"
#include <cmath>
#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>

double port_cosf64(double rad) {
    return cosf64(rad);
}

double port_sinf64(double rad) {
    return sinf64(rad);
}

static sf::RenderWindow *port_display = {};
static bool use_mouse = false;

void port_create_window(const char *caption) {
    port_display = new sf::RenderWindow(sf::VideoMode(250, 400), caption, sf::Style::None); // TODO: Add X move hint.
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
    auto &image = images[_image];
    unsigned int width = image.getSize().x;
    unsigned int height = image.getSize().y;
    rgbaData.resize(width * height);
    std::fill(rgbaData.begin(), rgbaData.end(), color_to_rgba(color));
    sf::Image imageData;
    imageData.create(width, height, reinterpret_cast<const sf::Uint8 *>(rgbaData.data()));
    image.loadFromImage(imageData);
}

void port_image_load(PortImage _image, PortColor *data, int size) {
    auto &image = images[_image];
    rgbaData.resize(size);
    for (int i = 0; i < size; i++) {
        auto c = color_to_rgba(data[i]);
        rgbaData[i] = c;
    }
    sf::Image imageData;
    imageData.create(image.getSize().x, image.getSize().y, reinterpret_cast<const sf::Uint8 *>(rgbaData.data()));
    image.loadFromImage(imageData);
}

void port_image_fillpoly(PortImage _dst, PortPoint *points, int size, PortImage _src, PortPoint srcPoint) {
    auto &dst = images[_dst];
    auto &src = images[_src];
    sf::ConvexShape convex; // TODO: Support concave shapes.
    convex.setPointCount(size);
    convex.setFillColor(src.copyToImage().getPixel(0, 0));
    for (int i = 0; i < size; i++) {
        convex.setPoint(i, sf::Vector2f((float) points[i].x, (float) points[i].y));
    }
    sf::RenderTexture renderTexture;
    renderTexture.create(dst.getSize().x, dst.getSize().y);
    renderTexture.clear();
    renderTexture.draw(sf::Sprite(dst));
    renderTexture.draw(convex);
    renderTexture.display();
    dst = renderTexture.getTexture();
}

void port_image_poly(PortImage _dst, PortPoint *points, int size, PortImage _src, PortPoint srcPoint) {
    auto &dst = images[_dst];
    auto &src = images[_src];

    sf::Vertex lines[size];
    for (int i = 0; i < size; i++) {
        lines[i] = sf::Vertex(sf::Vector2f((float) points[i].x, (float) points[i].y));
        lines[i].color = src.copyToImage().getPixel(0, 0);
    }
    sf::RenderTexture renderTexture;
    renderTexture.create(dst.getSize().x, dst.getSize().y);
    renderTexture.clear();
    renderTexture.draw(sf::Sprite(dst));
    renderTexture.draw(lines, size, sf::LineStrip);
    renderTexture.display();
    dst = renderTexture.getTexture();
}

void port_image_draw(PortImage _dst, PortRect r, PortImage _src, PortPoint p) {
    auto &dst = images[_dst];
    auto &src = images[_src];
    sf::Sprite sprite(src);
    sprite.setPosition((float) -p.x, (float) -p.y);
    // TODO: sprite.setTextureRect(sf::IntRect(r.min.x, r.min.y, r.max.x - r.min.x, r.max.y - r.min.y));
    sf::RenderTexture renderTexture;
    renderTexture.create(dst.getSize().x, dst.getSize().y);
    renderTexture.clear();
    renderTexture.draw(sf::Sprite(dst));
    renderTexture.draw(sprite);
    renderTexture.display();
    dst = renderTexture.getTexture();
}

void port_window_update(PortImage _image) {
    auto &image = images[_image];
    if (port_display->isOpen())
    {
        sf::Event event;
        while (port_display->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                port_display->close();
        }
        sf::Sprite sprite;
        sprite.setTexture(image);
        //port_display->clear();
        port_display->draw(sprite);
        port_display->display();
    }
}

void port_sleep(long millisecs) {
    sf::sleep(sf::milliseconds(millisecs));
}

PortTm port_localtime(long clock) {
    struct tm *timeinfo = localtime(&clock);
    return PortTm{
            .sec = timeinfo->tm_sec,
            .min = timeinfo->tm_min,
            .hour= timeinfo->tm_hour,
    };
}
