#pragma once
#include "Entity.h"
#include "Component.h"


class PositionComponent : public Component {
public:
    PositionComponent() = default;

    
    Position* getPosition() const { return parent_ ? parent_->getPosition() : position_; }
    double getRotation () const { return rotation; }

    void setPosition(Position& position) { position_ = &position; };

    void setRotation();



private:

    PositionComponent* parent_ = nullptr;

    int mass_ = -1;

    Position* position_;

    int speed_x_;
    int speed_y_;
    double rotation = -1;
};
