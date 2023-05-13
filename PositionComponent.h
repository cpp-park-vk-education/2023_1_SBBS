#pragma once
#include "Entity.h"
#include "Component.h"


class PositionComponent : public Component {
public:
    PositionComponent();

    Position* getPosition() const { return position_; }

    void setPosition(Position position);

private:

    PositionComponent* parent_ = nullptr;

    int mass_ = -1;

    Position* position_;

    int speed_x_;
    int speed_y_;
};
