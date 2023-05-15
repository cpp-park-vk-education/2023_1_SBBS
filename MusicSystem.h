#pragma once
#include "System.h"
#include "Types.h"
#include "Entity.h"


class MusicSystem : public System {
public:

    int update(sf::RenderWindow& window, std::vector<Entity>& scene) override;

};