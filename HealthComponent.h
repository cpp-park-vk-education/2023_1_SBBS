#pragma once
#include "Entity.h"
#include "Component.h"

class HealthComponent : public Component {
public:
    HealthComponent(bool mortal, bool afterlife, bool collidable_in_afterlife, int health = 0) : 
        mortal_(mortal), health_(health), afterlife_(afterlife), collidable_in_afterlife_(collidable_in_afterlife) {};

    bool isMortal();

    int getHealth();

    void setHealth(int health); //// нет сеттера?  нужно использовать setHealth(this.getHealth() - bullet.getDamage())

    bool hasAfterlife() { return afterlife_; };
    
    void setAfterlife();
    
    void set_dead(bool actual); // убрать

    void damage(int damage); // убрать 

    bool get_dead();

    bool get_mortal();

private:
    Entity* owner;

    bool collidable_in_afterlife_;

    bool afterlife_;

    bool dead_ = false;

    bool mortal_; 

    int health_;

    int damage_;
};
