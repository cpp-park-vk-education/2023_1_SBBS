#pragma once
#include "System.h"
#include "Types.h"
#include "Entity.h"

class MenuSystem : public System {
public:

    void surfMenu(std::vector<Entity> scene, std::vector<sf::Event> events);

};