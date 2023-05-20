#pragma once
#include "Entity.h"
#include "Component.h"

class HealthComponent : public Component {
public:
    HealthComponent(bool mortal, bool afterlife, bool collidable_in_afterlife, Entity* owner, int health = 0, int damage = 0) : 
        mortal_(mortal), health_(health), afterlife_(afterlife), 
        collidable_in_afterlife_(collidable_in_afterlife), owner_(owner), damage_(damage) {};

    bool isMortal();

    int getHealth();

    void setHealth(int health) {
        health_ = health;
        if (health_ <= 0) {
            dead_ = true;
            setAfterlife();
        }
    }

    bool hasAfterlife() { return afterlife_; };
    
    void setAfterlife();

    int getDamage() { return damage_; };

private:
    Entity* owner_;

    bool collidable_in_afterlife_;

    bool afterlife_;

    bool dead_ = false;

    bool mortal_; 

    int health_;

    int damage_;
};
