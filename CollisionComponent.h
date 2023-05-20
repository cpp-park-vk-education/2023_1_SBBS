#pragma once
#include "Entity.h"
#include "Component.h"
#include <math.h>
#include <iostream>

class CollisionComponent : public Component {
public:

    CollisionComponent(Position position, int rotation, int height, int width);

    CollisionComponent() {};

    void update(Position position, int rotation);

    bool checkCollision(CollisionComponent* tested_object);

    ~CollisionComponent() = default;

    void setPosition(Position& position);

    void setRotation(const int& coner);

    std::vector<Position> get_hitbox();

    bool checkBullet(Position beg, Position end);

    CollisionComponent(CollisionComponent* comp) = delete;  

    Position position_;

private:

    

    std::vector<Position> hitbox_;

    int rotation_;

    int height_ = -1;
    int width_ = -1;

    void (*onCollisionEvent)(Entity& collided);

};