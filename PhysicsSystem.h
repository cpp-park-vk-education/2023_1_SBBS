#pragma once
#include "System.h"
#include "Types.h"
#include "Entity.h"
#include "InputHandler.h"
#include <SFML/Graphics.hpp>

class PhysicsSystem : public System {
public:

    void updatePositions(sf::RenderWindow& window, std::vector<Entity>& scene);
};
