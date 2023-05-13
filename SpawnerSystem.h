#pragma once
#include "System.h"
#include"Entity.h"
#include "Types.h"

class SpawnerSystem : public System {
public:
    virtual Entity Spawn(ObjectType type, Position position);
};

class TankSpawner : public SpawnerSystem {
public:
    Entity Spawn(ObjectType type, Position position) override;
};

class BulletSpawner : public SpawnerSystem {
public:
    Entity Spawn(ObjectType type, Position position) override;
};

class WallSpawner : public SpawnerSystem {
public:
    Entity Spawn(ObjectType type, Position position) override;
};

class ButtonSpawner : public SpawnerSystem {
public:
    Entity Spawn(ObjectType type, Position position) override;
};

class BannerSpawner : public SpawnerSystem {
public:
    Entity Spawn(ObjectType type, Position position) override;
};
