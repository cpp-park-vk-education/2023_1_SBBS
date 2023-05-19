#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <unordered_map>
#include "Types.h"
#include "System.h"
#include "Entity.h"

class GameState {
public:

    virtual GameState* update(sf::RenderWindow& window) = 0;

    GameStateId getStateId() { return id_; };

protected:

    GameStateId id_;

    void addSystem(SystemId id, System* system);

    System* getSystemById(SystemId id);

	std::unordered_map<SystemId, System*> systems_;

    std::vector<Entity> scene_;
};

class MainMenuGameState :public GameState {
public:

    GameState* update(sf::RenderWindow& window) override;

    MainMenuGameState();
};

class HostMenuGameState :public GameState {
public:

    HostMenuGameState();

    GameState* update(sf::RenderWindow& window) override;
};

class ClientMenuGameState :public GameState {
public:

    ClientMenuGameState();

    GameState* update(sf::RenderWindow& window) override;
};

class PlayingState : public GameState {
public:

protected:
    Entity* getMyTank();

    void generateMap(const std::string& map_name, int my_tank_id);

    bool isDead(Entity* tank);
};

class HostPlayingGameState : public PlayingState {
public:
    HostPlayingGameState();

    GameState* update(sf::RenderWindow& window) override;

private:
};

class ClientPlayingGameState : public PlayingState {
public:

    GameState* update(sf::RenderWindow& window) override;


    ClientPlayingGameState();

private:
};


