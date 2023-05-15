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

protected:

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

class HostPlayingGameState : public GameState {
public:
    HostPlayingGameState();

    GameState* update(sf::RenderWindow& window) override;

private:

};

class ClientPlayingGameState : public GameState {
public:

    GameState* update(sf::RenderWindow& window) override;


    ClientPlayingGameState();

private:
    Entity* getMyTank();
};


