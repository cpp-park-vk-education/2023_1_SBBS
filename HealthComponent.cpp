#pragma once
#include "HealthComponent.h"
#include "GraphicsComponent.h"

void HealthComponent::setAfterlife(){
    owner_->deleteComponent(ComponentID::SoundComponent);


    if (!collidable_in_afterlife_) {
        owner_->deleteComponent(ComponentID::CollisionComponent);
    }
    GraphicsComponent* current_graph = dynamic_cast<GraphicsComponent*>(owner_->getComponentByID(ComponentID::GraphicsComponent));
    current_graph->setDeadSprite();
    owner_->setEntityID(0);
}

bool HealthComponent::isMortal() {
    return mortal_;
}

int HealthComponent::getHealth(){ 
    return health_; 
};

void HealthComponent::setHealth(int health) {

    if (mortal_) {
        health_ = health;

        if (health_ <= 0) {
            dead_ = true;
            setAfterlife();
        }
    }
}
