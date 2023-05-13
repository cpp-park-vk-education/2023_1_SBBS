#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


class GameState {
public:

    virtual GameState* update(sf::RenderWindow& window) = 0;
};

class MainMenuGameState :public GameState {
public:

    GameState* update(sf::RenderWindow& window) override;
};

class HostMenuGameState :public GameState {
public:

    GameState* update(sf::RenderWindow& window) override;
};

class ClientMenuGameState :public GameState {
public:

    GameState* update(sf::RenderWindow& window) override;
};

class HostPlayingGameState : public GameState {
public:

    GameState* update(sf::RenderWindow& window) override;
};

class ClientPlayingGameState : public GameState {
public:

    GameState* update(sf::RenderWindow& window) override;
};


