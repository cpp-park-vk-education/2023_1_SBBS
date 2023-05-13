#pragma once
#include "System.h"
#include "Types.h"
#include "Entity.h"
#include <SFML/Graphics.hpp>

class PhysicsSystem : public System {
public:

    void updatePositions(std::vector<bool> inputs, const sf::Mouse& mouse) {

        /*HealthComponent* temp_component = dynamic_cast<HealthComponent*>(scene[1].getComponentByID(ComponentID::HealthComponent));
        temp_component->setHealth(10);*/
    }

};
