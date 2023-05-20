#pragma once
#include "GameState.h"

SinglePlayerMenuGameState::SinglePlayerMenuGameState() {
	id_ = GameStateId::SingleMenu;
}

GameStateId SinglePlayerMenuGameState::update(sf::RenderWindow& window) {
	return id_;
}

