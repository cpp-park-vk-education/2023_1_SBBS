#pragma once
#include "System.h"
#include "Types.h"
#include "Entity.h"
#include "Input.h"
#include <SFML/Graphics.hpp>

class PhysicsSystem : public System {
public:

    void updatePositions(const Input& inputs, std::vector<Entity>& scene) {}

        /*HealthComponent* temp_component = dynamic_cast<HealthComponent*>(scene[1].getComponentByID(ComponentID::HealthComponent));
        temp_component->setHealth(10);*/
};
