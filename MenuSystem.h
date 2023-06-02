#pragma once
#include "System.h"
#include "Types.h"
#include "Entity.h"
#include <SFML/Graphics.hpp>

class MenuSystem : public System {
public:

    int update(sf::RenderWindow& window, std::vector<Entity*>& scene) override;
};