#pragma once
#include "GameState.h"

HostMenuGameState::HostMenuGameState() {
	id_ = GameStateId::HostMenu;
}

GameStateId HostMenuGameState::update(sf::RenderWindow& window) {
	return id_;
}