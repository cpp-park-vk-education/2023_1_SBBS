#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <unordered_map>
#include "Types.h"
#include "System.h"
#include "Entity.h"

class GameState {
public:

    virtual GameStateId update(sf::RenderWindow& window) = 0;

    GameStateId getStateId() { return id_; };

protected:

    GameStateId id_;

    void addSystem(SystemId id);

	std::vector<System*> systems_;

    std::vector<Entity*> scene_;
};

class MainMenuGameState :public GameState {
public:

    GameStateId update(sf::RenderWindow& window) override;

    MainMenuGameState();
};

class HostMenuGameState :public GameState {
public:

    HostMenuGameState();

    GameStateId update(sf::RenderWindow& window) override;
};

class ClientMenuGameState :public GameState {
public:

    ClientMenuGameState();

    GameStateId update(sf::RenderWindow& window) override;
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
    HostPlayingGameState(const std::string&);

    GameStateId update(sf::RenderWindow& window) override;

private:
};

class ClientPlayingGameState : public PlayingState {
public:

    GameStateId update(sf::RenderWindow& window) override;

    ClientPlayingGameState(const std::string& );

private:
};


