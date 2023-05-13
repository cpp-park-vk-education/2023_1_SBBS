#pragma once
#include "Entity.h"
#include "Component.h"

class HealthComponent : public Component {
public:
    HealthComponent(int health, bool mortal);

    bool isMortal();

    int getHealth() const { return health_; };

    void setHealth(int health);

private:

    bool mortal_ = false; 
    int health_ = -1;
};
