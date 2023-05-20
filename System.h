#pragma once
#include "Entity.h"
#include <vector>
#include <SFML/Graphics.hpp>

class System {
public:
	virtual int update(sf::RenderWindow& window, std::vector<Entity*>& scene) = 0;

	virtual ~System() {};
};