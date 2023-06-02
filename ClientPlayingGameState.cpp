#pragma once
#include "GameState.h"
#include "MusicSystem.h"
#include "GraphicsSystem.h"
#include "HealthComponent.h"
#include "PositionComponent.h"
#include "PhysicsSystem.h"
#include "InputHandler.h"
#include "SpawnerSystem.h"
#include <fstream>
#include <iostream>
#include <Windows.h>


ClientPlayingGameState::ClientPlayingGameState(const std::string& map_name) {
	id_ = GameStateId::ClientPlaying;

	generateMap(map_name);

	addSystem(SystemId::MusicSystemId);
	addSystem(SystemId::SoundSystemId);
	addSystem(SystemId::GraphicsSystemId);
	addSystem(SystemId::PhysicsSystemId);

	setMyTank();
};

GameStateId ClientPlayingGameState::update(sf::RenderWindow& window) {


	for (int i = 0; i < systems_.size(); ++i) {
		systems_[i]->update(window, scene_);
	}

	if (isDead(my_tank_)) {// сделать геймстейт после смерти или статистику игры
		
		return GameStateId::MainMenu;
	}

	return id_;
}


