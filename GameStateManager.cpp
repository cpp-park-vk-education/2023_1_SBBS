#include "GameStateManager.h"

void StateManager::changeState(GameStateId id) {
	std::string arg; 

	if (curr_state_) {
		arg = curr_state_->getStateArgument(); // has map name for playing states
		delete curr_state_;
	}

	switch (id) {
	case GameStateId::MainMenu:
		curr_state_ = new MainMenuGameState;
		break;
	case GameStateId::HostMenu:
		curr_state_ = new HostMenuGameState;
		break;
	case GameStateId::ClientMenu:
		curr_state_ = new ClientMenuGameState;
	case GameStateId::SingleMenu:
		curr_state_ = new SinglePlayerMenuGameState;
		break;
	case GameStateId::HostPlaying:
		curr_state_ = new HostPlayingGameState(arg);
		break;
	case GameStateId::ClientPlaying:
		curr_state_ = new ClientPlayingGameState(arg);
		break;
	case GameStateId::SinglePlaying:
		curr_state_ = new SinglePlayingGameState(arg);
	default:
		break;
	}
}

void StateManager::run(sf::RenderWindow& window) {
	GameStateId nextGameState = curr_state_->update(window);

	if (nextGameState != curr_state_->getStateId()) {
		changeState(nextGameState);
	}
};
