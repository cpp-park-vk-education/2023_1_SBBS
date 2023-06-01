#pragma once
#include "PhysicsSystem.h"
#include "PositionComponent.h"
#include "Types.h"
#include <math.h>
#include "CollisionComponent.h"
#include <iostream>
#include "SpawnerSystem.h"
#include "HealthComponent.h"
#include "netConnect.h"
#include "networkCodes.h"
#include "ShootComponent.h"
#include "SoundComponent.h"
#include "InputHandler.h"
#include "GameSingleton.h"

int PhysicsSystem::update(sf::RenderWindow& window, std::vector<Entity*>& scene) {
    
    for (int i = Game::getInstance().getFirstCollidable(); i < scene.size(); ++i) {
        PositionComponent* current_component = dynamic_cast<PositionComponent*>(scene[i]->getComponentByID(ComponentID::PositionComponent));
        current_component->update(window, scene, i);
    }

    return 0;
}
