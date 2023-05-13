#pragma once
#include "System.h"
#include"Entity.h"
#include "Types.h"



class SpawnerSystem : public System {
public:
    virtual std::vector<Entity> Spawn(Position position, char subType) = 0;
    static SpawnerSystem* getSpawner(ObjectType type);
};

class TankSpawner : public SpawnerSystem {
public:
    std::vector<Entity> Spawn(Position position, char subType) override;
};

class BulletSpawner : public SpawnerSystem {
public:
    std::vector<Entity> Spawn(Position position, char subType) override;
};

class WallSpawner : public SpawnerSystem {
public:
    std::vector<Entity> Spawn(Position position, char subType) override;
};

class ButtonSpawner : public SpawnerSystem {
public:
    std::vector<Entity> Spawn(Position position, char subType) override;
};

class BannerSpawner : public SpawnerSystem {
public:
    std::vector<Entity> Spawn(Position position, char subType) override;
};
