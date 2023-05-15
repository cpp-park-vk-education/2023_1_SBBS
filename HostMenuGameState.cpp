#pragma once
#include "GameState.h"

HostMenuGameState::HostMenuGameState() {
	id_ = GameStateId::HostMenu;
}

GameState* HostMenuGameState::update(sf::RenderWindow& window) {
	return this;
}