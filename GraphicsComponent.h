#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Component.h"

class GraphicsComponent : public Component {
public:
    GraphicsComponent() = default;

    bool layer = 0;

    void setImage(sf::Image image) {
        obj_image_ = image;
        obj_image_.createMaskFromColor(sf::Color::White);
        obj_texture_.loadFromImage(obj_image_);
        obj_sprite_.setTexture(obj_texture_);

        obj_sprite_.setScale(0.5f, 0.5f);
        obj_sprite_.setOrigin(50, 50);
        //Возможно, сюда надо передать коэффициент сжатия. Либо же сделать его одинаковым для всех
    };

    void setOrigin(int x, int y) {
        obj_sprite_.setOrigin(x, y);
    }

    void setTexture(sf::Texture texture);

    void setSprite(sf::Sprite sprite);


    sf::Sprite getSprite() { return obj_sprite_; }
    /*sf::Texture getTexture() { return obj_texture_; }*/

private:
    sf::Image obj_image_;
    sf::Texture obj_texture_;
    sf::Sprite obj_sprite_;
};
