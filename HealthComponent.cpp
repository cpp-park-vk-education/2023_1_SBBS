#pragma once
#include "HealthComponent.h"

bool HealthComponent::isMortal() {
    return mortal_;
}

int HealthComponent::getHealth(){ 
    return health_; 
};

void HealthComponent::set_dead(bool actual) {
    dead_ = actual;
}

void HealthComponent::damage(int damage) {
    health_ -= damage;
    if (health_ < 1) {
        dead_ = true;
        mortal_ = false;
    }
}

bool HealthComponent::get_dead() {
    return dead_;
}

bool HealthComponent::get_mortal() {
    return mortal_;
}

