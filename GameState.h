#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <unordered_map>
#include "Types.h"
#include "System.h"
#include "Entity.h"
#include "SpawnId.h"

class GameState {
public:

    virtual GameStateId update(sf::RenderWindow& window) = 0;

    GameStateId getStateId() { return id_; };

    void setStateArgument(const std::string& arg) { state_argument_ = arg; }

    std::string getStateArgument() { return state_argument_; }

    virtual ~GameState();

protected:

    GameStateId id_;

    void addSystem(SystemId id);

	std::vector<System*> systems_;

    std::vector<Entity*> scene_;

    std::string state_argument_ = std::string(" ");
};

class MainMenuGameState :public GameState {
public:

    GameStateId update(sf::RenderWindow& window) override;

    MainMenuGameState();
};




class SubMenuState : public GameState {
public:
    SubMenuState() {};

    virtual ~SubMenuState();

protected:
    void setTankHull(const char& hull) { tank_hull = hull; }
    void setTankTurret(const char& turret) { tank_turret = turret; }
    char tank_hull = tank_hull_1;
    char tank_turret = tank_turret_1;
};

class HostMenuGameState :public SubMenuState {
public:
    HostMenuGameState();

    GameStateId update(sf::RenderWindow& window) override;
};

class ClientMenuGameState :public SubMenuState {
public:
    ClientMenuGameState();

    GameStateId update(sf::RenderWindow& window) override;
};

class SinglePlayerMenuGameState : public SubMenuState {
public:
    SinglePlayerMenuGameState();

    GameStateId update(sf::RenderWindow& window) override;
};




class PlayingState : public GameState {
public:
    static int getMyEntityId() { return my_entity_id; }

protected:

    static int my_entity_id;

    void setMyTank();

    Entity* my_tank_ = nullptr;

    void generateMap(const std::string& map_name);

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

};

class SinglePlayingGameState : public PlayingState {
public:
    GameStateId update(sf::RenderWindow& window) override;

    SinglePlayingGameState(const std::string&);


};
