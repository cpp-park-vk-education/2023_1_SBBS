#pragma once
#include "Entity.h"
#include "Component.h"

class HealthComponent : public Component {
public:
    HealthComponent(bool mortal, int health = 0) : mortal_(mortal), health_(health) {};

    bool isMortal();

    int getHealth();

    void setHealth(int health); //// нет сеттера?

    void set_dead(bool actual);

    void damage(int damage);

    bool get_dead();

    bool get_mortal();

private:
    bool dead_ = false;
    bool mortal_; 
    int health_;
};
