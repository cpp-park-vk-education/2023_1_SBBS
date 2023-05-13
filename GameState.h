#pragma once

class GameState {
public:

    virtual GameState* update(std::vector<sf::Event> events, sf::Mouse& mouse);
};

class MainMenuGameState :public GameState {
public:

    GameState* update(std::vector<sf::Event> events, sf::Mouse& mouse) override;
};

class HostMenuGameState :public GameState {
public:

    GameState* update(std::vector<sf::Event> events, sf::Mouse& mouse) override;
};

class ClientMenuGameState :public GameState {
public:

    GameState* update(std::vector<sf::Event> events, sf::Mouse& mouse) override;
};

class HostPlayingGameState : public GameState {
public:

    GameState* update(std::vector<sf::Event> events, sf::Mouse& mouse) override;
};

class ClientPlayingGameState : public GameState {
public:

    GameState* update(std::vector<sf::Event> events, sf::Mouse& mouse) override;
};


