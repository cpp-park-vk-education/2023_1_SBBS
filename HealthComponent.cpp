#pragma once
#include "HealthComponent.h"
#include "GraphicsComponent.h"

void HealthComponent::setAfterlife(){

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

