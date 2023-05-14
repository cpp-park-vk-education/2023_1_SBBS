#pragma once
#include "System.h"
#include "Types.h"
#include "Entity.h"
#include <SFML/Graphics.hpp>

class MenuSystem : public System {
public:

    void surfMenu(std::vector<Entity>& scene, sf::RenderWindow& window);
};