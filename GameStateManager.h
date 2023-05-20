#include "GameState.h"
#include <SFML/Graphics.hpp>

class StateManager {
public:

	GameStateId getStateId() { return curr_state_->getStateId(); }

	void changeState(GameStateId id, const std::string& arg = std::string());

	void run(sf::RenderWindow& window);

private:
	GameState* curr_state_ = nullptr;
};