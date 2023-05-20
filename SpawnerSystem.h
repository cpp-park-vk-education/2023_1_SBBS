#pragma once
#include "System.h"
#include"Entity.h"
#include "Types.h"
#include <unordered_map>

class Spawner {
public:
    virtual Entity* Spawn(Position position, char subType) = 0;
};

class SpawnerSystem : public System {
public:

    Spawner* getSpawner(ObjectType type);

    int update(sf::RenderWindow& window, std::vector<Entity*>& scene) override;

private:
    std::unordered_map<ObjectType, Spawner*> spawners_;

};

class TankSpawner : public Spawner {
public:
    Entity* Spawn(Position position, char subType) override;
};

class TurretSpawner : public Spawner {
public:
    Entity* Spawn(Position position, char subType) override;
};

class BulletSpawner : public Spawner {
public:
    Entity* Spawn(Position position, char subType) override;
};

class MapSpawner : public Spawner {
public:
    Entity* Spawn(Position position, char subType) override;
};

class ButtonSpawner : public Spawner {
public:
    Entity* Spawn(Position position, char subType) override;
};

class BannerSpawner : public Spawner {
public:
    Entity* Spawn(Position position, char subType) override;
};
