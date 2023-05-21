#pragma once
#include "System.h"
#include"Entity.h"
#include "Types.h"
#include <unordered_map>

class Spawner {
public:
    virtual Entity* Spawn(Position position, char subType) = 0;
};

enum class OwnerType {
    Network, Bot, Player
};

class SpawnerSystem : public System {
public:

    Spawner* getSpawner(ObjectType type); /// видимо не нужен 

    int update(sf::RenderWindow& window, std::vector<Entity*>& scene) override;

private:
    std::unordered_map<ObjectType, Spawner*> spawners_;

};

class PlayingObjectSpawner : public Spawner {
public:
    void setOwnerType(OwnerType type) { current_type_ = type; }

    OwnerType getOwnerType() { return current_type_; }

protected:
    OwnerType current_type_;
};

class TankSpawner : public PlayingObjectSpawner {
public:
    Entity* Spawn(Position position, char subType) override;
};

class TurretSpawner : public PlayingObjectSpawner {
public:
    Entity* Spawn(Position position, char subType) override;
};

class BulletSpawner : public PlayingObjectSpawner {
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
