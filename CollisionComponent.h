#pragma once
#include "Entity.h"
#include "Component.h"

class CollisionComponent : public Component {
public:

    Entity* checkCollision(CollisionComponent* tested_object);

    ~CollisionComponent();

    CollisionComponent(CollisionComponent* comp) = delete;

    CollisionComponent operator= (CollisionComponent) = delete;

private:

    int height_ = -1;
    int width_ = -1;

    void (*onCollisionEvent)(Entity& collided);

};