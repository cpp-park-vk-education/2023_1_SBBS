#pragma once
#include "GameState.h"

SinglePlayerMenuGameState::SinglePlayerMenuGameState() {
	id_ = GameStateId::SingleMenu;

	addSystem(SystemId::GraphicsSystemId);
	addSystem(SystemId::MenuSystemId);
	addSystem(SystemId::MusicSystemId);
}

GameStateId SinglePlayerMenuGameState::update(sf::RenderWindow& window) {
	return id_;
}

