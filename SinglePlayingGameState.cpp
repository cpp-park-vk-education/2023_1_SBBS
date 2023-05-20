#pragma once
#include "GameState.h"

SinglePlayingGameState::SinglePlayingGameState(const std::string&) {
	id_ = GameStateId::SinglePlaying;
}

GameStateId SinglePlayingGameState::update(sf::RenderWindow& window) {
	return id_;
}

