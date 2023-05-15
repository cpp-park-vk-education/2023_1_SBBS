#pragma once
#include "System.h"
#include "Entity.h"
#include "SFML/Graphics.hpp"

class SoundSystem : public System {

	int update(sf::RenderWindow& window, std::vector<Entity>& scene) override;
};
