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

HostPlayingGameState::HostPlayingGameState(const std::string& map_name) {
	id_ = GameStateId::HostPlaying;

	generateMap(map_name);

	addSystem(SystemId::MusicSystemId);
	addSystem(SystemId::GraphicsSystemId);
	addSystem(SystemId::PhysicsSystemId);
	addSystem(SystemId::MenuSystemId);
	addSystem(SystemId::PauseSystemId);
	addSystem(SystemId::SpawnerSystemId);

	setMyTank();
}

GameStateId HostPlayingGameState::update(sf::RenderWindow& window) {

	for (int i = 0; i < systems_.size(); ++i) {
		systems_[i]->update(window,scene_);
	}

	//if (isDead(my_tank_)) { если хост умирает, не должно выйти в меню
	// 
	//	return GameStateId::MainMenu;
	//}	

	return id_;
}
