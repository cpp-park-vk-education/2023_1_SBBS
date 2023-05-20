#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Component.h"

class GraphicsComponent : public Component {
public:
    GraphicsComponent() = default;

    bool layer = 0;

    void setAliveImage(sf::Image aliveimage);

    void setDeadImage(sf::Image deadimage);

    void setDeadSprite();

    void setOrigin(int x, int y) { obj_sprite_.setOrigin(x, y); }

    void setTexture(sf::Texture texture); ///////////////// нужно ли?

    void setSprite(sf::Sprite sprite); ////// нужно ли? 

    sf::Sprite getSprite() { return obj_sprite_; }
    /*sf::Texture getTexture() { return obj_texture_; }*/

private:
    sf::Image dead_image_;
    sf::Image alive_image_;
    sf::Texture alive_texture_;
    sf::Texture dead_texture_;
    sf::Sprite obj_sprite_;
};
