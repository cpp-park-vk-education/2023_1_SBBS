#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Component.h"

class GraphicsComponent : public Component {
public:
    GraphicsComponent() = default;

    bool layer = 0;

    void setAliveImage(sf::Image aliveimage) { 
        alive_image_ = aliveimage;
        alive_image_.createMaskFromColor(sf::Color::White);
        alive_texture_.loadFromImage(alive_image_);
        obj_sprite_.setTexture(alive_texture_);

        obj_sprite_.setScale(0.5f, 0.5f);
        obj_sprite_.setOrigin(50, 50);
        //Возможно, сюда надо передать коэффициент сжатия. Либо же сделать его одинаковым для всех
    };

    void setDeadImage(sf::Image deadimage) {
        dead_image_ = deadimage;
        dead_image_.createMaskFromColor(sf::Color::White);
        dead_texture_.loadFromImage(dead_image_);
        obj_sprite_.setTexture(alive_texture_);
    };

    void setDeadSprite() {
        obj_sprite_.setTexture(dead_texture_);
        obj_sprite_.setScale(0.5f, 0.5f);
        obj_sprite_.setOrigin(50, 50);
    }

    void setOrigin(int x, int y) {
        obj_sprite_.setOrigin(x, y);
    }

    void setTexture(sf::Texture texture);

    void setSprite(sf::Sprite sprite);

    bool checkBullet(Position beg, Position end);// спросить у владоса зачем это 

    sf::Sprite getSprite() { return obj_sprite_; }
    /*sf::Texture getTexture() { return obj_texture_; }*/

private:
    sf::Image dead_image_;
    sf::Image alive_image_;
    sf::Texture alive_texture_;
    sf::Texture dead_texture_;
    sf::Sprite obj_sprite_;
};
