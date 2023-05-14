#pragma once
#include "Entity.h"
#include "Component.h"
#include "GameState.h"
#include <SFML/Graphics.hpp>

class ClickComponent : public Component {
public:
    ClickComponent(int left, int top, int width, int height) : buttonHitBox_(sf::Rect<int>(left,top,width,height)) {}

    GameState* changeState() { return state_; };

private:
    GameState* state_;

    sf::Rect<int> buttonHitBox_;

    Entity* owner_ = nullptr;
};
