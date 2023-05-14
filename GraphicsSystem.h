#pragma once
#include "System.h"
#include "Types.h"
#include "Entity.h"
#include <SFML/Graphics.hpp>

class GraphicsSystem : public System {
public:
    void renderScene(std::vector<Entity>& scene, sf::RenderWindow& window);
};