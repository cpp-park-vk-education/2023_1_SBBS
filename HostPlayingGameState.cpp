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

	generateMap(std::string(map_name), 2);


	//addSystem(SystemId::MusicSystemId, new MusicSystem);
	addSystem(SystemId::GraphicsSystemId, new GraphicsSystem);
	addSystem(SystemId::PhysicsSystemId, new PhysicsSystem);


	//ms.playMusic(scene); menu music
}

GameStateId HostPlayingGameState::update(sf::RenderWindow& window) {


	getSystemById(SystemId::PhysicsSystemId)->update(window, scene_);
	getSystemById(SystemId::GraphicsSystemId)->update(window, scene_);

	Entity* my_tank = getMyTank();

	//if (isDead(my_tank)) { если хост умирает, не должно выйти в меню
	// 
	//	return GameStateId::MainMenu;
	//}	

	return id_;
}
