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

	//scene.push_back(bs.Spawn(Position(0, 0), 's')[0]); /// menu music


	generateMap(std::string("Maps/lvl4.txt"), 0);

	addSystem(SystemId::MusicSystemId);
	addSystem(SystemId::SoundSystemId);
	addSystem(SystemId::GraphicsSystemId);
	addSystem(SystemId::PhysicsSystemId);

	//ms.playMusic(scene); menu music
};

GameStateId ClientPlayingGameState::update(sf::RenderWindow& window) {


	for (int i = 0; i < systems_.size(); ++i) {
		systems_[i]->update(window, scene_);
	}


	Entity* my_tank = getMyTank();

	if (isDead(my_tank)) {// сделать геймстейт после смерти или статистику игры
		
		return GameStateId::MainMenu;
	}

	return id_;
}


