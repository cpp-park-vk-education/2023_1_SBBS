#include "GameState.h"
#include <SFML/Graphics.hpp>

class StateManager {
public:

	GameStateId getStateId() { return curr_state_->getStateId(); }

	void changeState(GameStateId id);

	void run(sf::RenderWindow& window);

	StateManager() = default;

	StateManager(StateManager&) = delete;

	~StateManager() { delete curr_state_; };

private:
	GameState* curr_state_ = nullptr;
};