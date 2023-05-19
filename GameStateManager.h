#include "GameState.h"
#include <SFML/Graphics.hpp>

class StateManager {
public:

	GameStateId getStateId() { return curr_state_->getStateId(); }

	void changeState(GameStateId id, const std::string& arg  = std::string()) {
		if (curr_state_) {
			delete curr_state_;
		}

		switch (id){ 
		case GameStateId::MainMenu:
			curr_state_ = new MainMenuGameState;
			break;
		case GameStateId::HostMenu:
			curr_state_ = new HostMenuGameState;
			break;
		case GameStateId::ClientMenu:
			curr_state_ = new ClientMenuGameState;
			break;
		case GameStateId::HostPlaying:
			curr_state_ = new HostPlayingGameState(arg);
			break;
		case GameStateId::ClientPlaying:
			curr_state_ = new ClientPlayingGameState(arg);
			break;
		default:
			break;
		}
	}

	void run(sf::RenderWindow& window) {
		GameStateId nextGameState = curr_state_->update(window);

		if (nextGameState != curr_state_->getStateId()) { ///////////////////////// вставить выбор карты
			changeState(nextGameState, std::string("Maps/lvlTest2.txt"));
		}
	};


private:
	GameState* curr_state_ = nullptr;
};