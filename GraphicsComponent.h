#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Component.h"

class GraphicsComponent : public Component {
public:
    GraphicsComponent() = default;

    bool layer;

    void setImage(sf::Image image) {};

    void setTexture(sf::Texture texture);

    void setSprite(sf::Sprite sprite);


    sf::Sprite* getSprite() { return& obj_sprite_; }

private:
    sf::Image obj_image_;
    sf::Texture obj_texture_;
    sf::Sprite obj_sprite_;
};
