#pragma once
#include "GameState.h"
#include "InputHandler.h"
#include "GameSingleton.h"
#include "SpawnerSystem.h"

SinglePlayingGameState::SinglePlayingGameState(const std::string& map_name) {
	id_ = GameStateId::SinglePlaying;

	generateMap(map_name);

	addSystem(SystemId::MusicSystemId);
	addSystem(SystemId::SoundSystemId);
	addSystem(SystemId::GraphicsSystemId);
	addSystem(SystemId::PhysicsSystemId);
	addSystem(SystemId::MenuSystemId);
	addSystem(SystemId::PauseSystemId);

	setMyTank();
}

GameStateId SinglePlayingGameState::update(sf::RenderWindow& window) {

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

		static bool flag = true;
		if (flag) {
			BannerSpawner bs;
			Entity* wasted = bs.Spawn(Position(), wasted_banner);
			scene_.push_back(wasted);
			std::cout << "wasted\n";
			flag = false;
		}
		//return GameStateId::MainMenu;
	}

	return id_;
}

