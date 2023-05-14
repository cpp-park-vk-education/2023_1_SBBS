#pragma once
#include "Entity.h"
#include "Component.h"

class HealthComponent : public Component {
public:
    HealthComponent(bool mortal, int health = 0);

    bool isMortal();

    int getHealth() const { return health_; };

    void setHealth(int health);

private:

    bool mortal_; 
    int health_;
};
