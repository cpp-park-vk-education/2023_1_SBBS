#pragma once
#include "GameState.h"

ClientMenuGameState::ClientMenuGameState() {
	id_ = GameStateId::ClientMenu;
}

GameState* ClientMenuGameState::update(sf::RenderWindow& window) {
	return this;
}