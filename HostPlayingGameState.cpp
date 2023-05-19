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

	//scene.push_back(bs.Spawn(Position(0, 0), 's')[0]); /// menu music

	//generateMap(std::string(map_name), 2);
	generateMap(std::string("Maps/lvlTest2.txt"), 1);

	addSystem(SystemId::MusicSystemId);
	addSystem(SystemId::GraphicsSystemId);
	addSystem(SystemId::PhysicsSystemId);

}

GameStateId HostPlayingGameState::update(sf::RenderWindow& window) {

	for (int i = 0; i < systems_.size(); ++i) {
		systems_[i]->update(window,scene_);
	}

	Entity* my_tank = getMyTank();

	//if (isDead(my_tank)) { если хост умирает, не должно выйти в меню
	// 
	//	return GameStateId::MainMenu;
	//}	

	return id_;
}
