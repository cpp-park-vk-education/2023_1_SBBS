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
#include "SpawnID.h"
#include "GameSingleton.h"


ClientPlayingGameState::ClientPlayingGameState(const std::string& map_name) {
	id_ = GameStateId::ClientPlaying;

	generateMap(map_name);

	addSystem(SystemId::MusicSystemId);
	addSystem(SystemId::SoundSystemId);
	addSystem(SystemId::GraphicsSystemId);
	addSystem(SystemId::PhysicsSystemId);
	addSystem(SystemId::MenuSystemId);
	addSystem(SystemId::PauseSystemId);

	setMyTank();
};

GameStateId ClientPlayingGameState::update(sf::RenderWindow& window) {


	Input input;
	input.handleInput(window);

	int chosen_button_id = 0;
	for (int i = 0; i < systems_.size(); ++i) {
		int sys_output = systems_[i]->update(window, scene_); // ненулевой будет только в menusystem
		if (sys_output) {
			chosen_button_id = sys_output;
		}
		//std::cout << chosen_button_id << std::endl;

	}

	if (input.mouse_click_) {
		switch (chosen_button_id)
		{
		case back_to_main_menu_button_id:
			return GameStateId::MainMenu;
			break;
		case resume_game_button_id:
			Game::getInstance().setGamePause(false);
			break;
		default: break;
		}
	}

	if (isDead(my_tank_)) {// сделать геймстейт после смерти или статистику игры
		
		return GameStateId::MainMenu;
	}

	return id_;
}


