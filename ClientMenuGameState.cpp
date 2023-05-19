#pragma once
#include "GameState.h"

ClientMenuGameState::ClientMenuGameState() {
	id_ = GameStateId::ClientMenu;
}

GameStateId ClientMenuGameState::update(sf::RenderWindow& window) {
	return id_;
}