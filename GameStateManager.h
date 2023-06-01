#include "GameState.h"
#include <SFML/Graphics.hpp>

class StateManager {
public:

	GameStateId getStateId() { return curr_state_->getStateId(); }

	void changeState(GameStateId id);

	void run();

	StateManager(sf::RenderWindow& window_) : window(window_) {};

	StateManager(StateManager&) = delete;

	~StateManager() { delete curr_state_; };

private:
	GameState* curr_state_ = nullptr;

	sf::RenderWindow& window;
};