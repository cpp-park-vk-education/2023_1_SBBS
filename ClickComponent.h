#pragma once
#include "Entity.h"
#include "Component.h"
#include "GameState.h"
#include <SFML/Graphics.hpp>

class ClickComponent : public Component {
public:
    ClickComponent(int left, int top, int width, int height) : buttonHitBox_(sf::Rect<int>(left,top,width,height)) {}

    void setButtonId(int id) { button_id_ = id; }

    int getButtonId() { return button_id_; }

    bool isChosen(sf::Window& window) { return buttonHitBox_.contains(sf::Mouse::getPosition(window)); }

    char getType() { return type_; }

private:
    
    int button_id_;

    char type_;

    sf::Rect<int> buttonHitBox_;
};
