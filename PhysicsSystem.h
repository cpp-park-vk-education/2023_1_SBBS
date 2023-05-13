#pragma once
#include "System.h"
#include "Types.h"
#include "Entity.h"
#include <SFML/Graphics.hpp>

class PhysicsSystem : public System {
public:

    void updatePositions(std::vector<Entity> scene, std::vector<sf::Event> events) {

        /*HealthComponent* temp_component = dynamic_cast<HealthComponent*>(scene[1].getComponentByID(ComponentID::HealthComponent));
        temp_component->setHealth(10);*/
    }

};
