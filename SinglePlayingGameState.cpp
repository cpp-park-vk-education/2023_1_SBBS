#pragma once
#include "GameState.h"

SinglePlayingGameState::SinglePlayingGameState(const std::string& map_name) {
	id_ = GameStateId::SinglePlaying;

	generateMap(map_name);

	addSystem(SystemId::MusicSystemId);
	addSystem(SystemId::SoundSystemId);
	addSystem(SystemId::GraphicsSystemId);
	addSystem(SystemId::PhysicsSystemId);

	setMyTank();
}

GameStateId SinglePlayingGameState::update(sf::RenderWindow& window) {

	for (int i = 0; i < systems_.size(); ++i) {
		systems_[i]->update(window, scene_);
	}

	if (isDead(my_tank_)) {// сделать геймстейт после смерти или статистику игры

		return GameStateId::MainMenu;
	}

	return id_;
}

