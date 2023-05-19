#include "GameState.h"

class StateManager {

	void changeState(GameStateId id) {
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
			curr_state_ = new HostPlayingGameState;
			break;
		case GameStateId::ClientPlaying:
			curr_state_ = new ClientPlayingGameState;
			break;
		default:
			break;
		}
	}

	void run();


private:
	GameState* curr_state_;
};