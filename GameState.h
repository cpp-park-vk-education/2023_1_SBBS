#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

enum class Input {
    MoveUp,MoveDown,MoveLeft,MoveRight
};

class GameState {
public:

    virtual GameState* update(const std::vector<sf::Event>& events, const sf::Mouse& mouse) = 0;
};

class MainMenuGameState :public GameState {
public:

    GameState* update(const std::vector<sf::Event>& events, const sf::Mouse& mouse) override;
};

class HostMenuGameState :public GameState {
public:

    GameState* update(const std::vector<sf::Event>& events, const sf::Mouse& mouse) override;
};

class ClientMenuGameState :public GameState {
public:

    GameState* update(const std::vector<sf::Event>& events, const sf::Mouse& mouse) override;
};

class HostPlayingGameState : public GameState {
public:

    GameState* update(const std::vector<sf::Event>& events, const sf::Mouse& mouse) override;
};

class ClientPlayingGameState : public GameState {
public:

    GameState* update(const std::vector<sf::Event>& events, const sf::Mouse& mouse) override;
};


