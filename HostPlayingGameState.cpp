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

HostPlayingGameState::HostPlayingGameState() {
	id_ = GameStateId::HostPlaying;

	

	//scene.push_back(bs.Spawn(Position(0, 0), 's')[0]); /// menu music


	generateMap(std::string("Maps/lvlTest2.txt"), 2);


	//addSystem(SystemId::MusicSystemId, new MusicSystem);
	addSystem(SystemId::GraphicsSystemId, new GraphicsSystem);
	addSystem(SystemId::PhysicsSystemId, new PhysicsSystem);


	//ms.playMusic(scene); menu music
}

GameState* HostPlayingGameState::update(sf::RenderWindow& window) {


	getSystemById(SystemId::PhysicsSystemId)->update(window, scene_);
	getSystemById(SystemId::GraphicsSystemId)->update(window, scene_);

	Entity* my_tank = getMyTank();

	if (isDead(my_tank) && !window.isOpen()) {

		return new MainMenuGameState();
	}	

	return this;
}
