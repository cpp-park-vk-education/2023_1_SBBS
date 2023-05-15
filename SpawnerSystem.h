#pragma once
#include "System.h"
#include"Entity.h"
#include "Types.h"



class SpawnerSystem {
public:
    virtual Entity Spawn(Position position, char subType) = 0;
    static SpawnerSystem* getSpawner(ObjectType type);
};

class TankSpawner : public SpawnerSystem {
public:
    Entity Spawn(Position position, char subType) override;
};

class TurretSpawner : public SpawnerSystem {
public:
    Entity Spawn(Position position, char subType) override;
};

class BulletSpawner : public SpawnerSystem {
public:
    Entity Spawn(Position position, char subType) override;
};

class MapSpawner : public SpawnerSystem {
public:
    Entity Spawn(Position position, char subType) override;
};

class ButtonSpawner : public SpawnerSystem {
public:
    Entity Spawn(Position position, char subType) override;
};

class BannerSpawner : public SpawnerSystem {
public:
    Entity Spawn(Position position, char subType) override;
};
