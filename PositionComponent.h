#pragma once
#include "Entity.h"
#include "Component.h"




class PositionComponent : public Component {
public:
    PositionComponent() = default;

    
    Position* getPosition() const { 
        return parent_ ? parent_->getPosition() : position_; 
    }

    int getSpeed() const { 
        return speed_; 
    }

    void setSpeed(int speed) { speed_ = speed; }

    int getRotation() { return rotation_; }

    void setPosition(Position& position) { position_ = &position; };

    void setPosition(Position* position) { position_ = position; };

    void setRotation(const int& coner) {
        rotation_ = coner;
    }

    void setParent(PositionComponent* parent) { parent_ = parent; }

private:

    PositionComponent* parent_ = nullptr;

    Position* position_;

    int speed_;

    int rotation_;
};
