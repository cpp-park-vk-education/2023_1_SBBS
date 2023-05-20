#include "GraphicsComponent.h"


void GraphicsComponent::setAliveImage(sf::Image aliveimage) {
    alive_image_ = aliveimage;
    alive_image_.createMaskFromColor(sf::Color::White);
    alive_texture_.loadFromImage(alive_image_);
    obj_sprite_.setTexture(alive_texture_);

    obj_sprite_.setScale(0.5f, 0.5f);
    obj_sprite_.setOrigin(50, 50);
    //Возможно, сюда надо передать коэффициент сжатия. Либо же сделать его одинаковым для всех
};

void GraphicsComponent::setDeadImage(sf::Image deadimage) {
    dead_image_ = deadimage;
    dead_image_.createMaskFromColor(sf::Color::White);
    dead_texture_.loadFromImage(dead_image_);
    obj_sprite_.setTexture(alive_texture_);
};

void GraphicsComponent::setDeadSprite() {
    obj_sprite_.setTexture(dead_texture_);
    obj_sprite_.setScale(0.5f, 0.5f);
    obj_sprite_.setOrigin(50, 50);
}
