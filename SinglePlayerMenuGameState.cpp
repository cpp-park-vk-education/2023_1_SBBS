#pragma once
#include "GameState.h"
#include "SpawnerSystem.h"
#include "SpawnID.h"
#include "InputHandler.h"
#include "GameSingleton.h"

SinglePlayerMenuGameState::SinglePlayerMenuGameState() {
	id_ = GameStateId::SingleMenu;

	addSystem(SystemId::GraphicsSystemId);
	addSystem(SystemId::MenuSystemId);
	addSystem(SystemId::MusicSystemId);

	BannerSpawner banner_spawner;
	ButtonSpawner button_spawner;


	//Спавн фона одиночного меню
	Position banner_pos(0, 0);

	Entity* temp_ent = nullptr;

	temp_ent = banner_spawner.Spawn(banner_pos, single_banner);//// убрать магическую константу
	scene_.push_back(temp_ent);


	//Спавн кнопки назад
	Position back_button_pos(200, 800);	// Эта кнопка будет возвращать игрока в главное меню


	temp_ent = button_spawner.Spawn(back_button_pos, back);
	scene_.push_back(temp_ent);

	// Спавн кнопки "Играть"
	Position connect_button_pos(1400, 800);

	temp_ent = button_spawner.Spawn(connect_button_pos, play);
	scene_.push_back(temp_ent);

	// Спавн Выбора скина танка. Две башни и два корпуса
	Position hull_1_pos(1300, 350);
	Position hull_2_pos(1650, 350);
	Position turret_1_pos(1300, 600);
	Position turret_2_pos(1650, 600);

	temp_ent = button_spawner.Spawn(hull_1_pos, tank_hull_1);
	scene_.push_back(temp_ent);

	temp_ent = button_spawner.Spawn(hull_2_pos, tank_hull_2);
	scene_.push_back(temp_ent);

	temp_ent = button_spawner.Spawn(turret_1_pos, tank_turret_1);
	scene_.push_back(temp_ent);

	temp_ent = button_spawner.Spawn(turret_2_pos, tank_turret_2);
	scene_.push_back(temp_ent);


	// Спавн кнопок выбора карты
	Position map_1_pos(120, 300);
	Position map_2_pos(520, 300);
	Position map_3_pos(120, 550);
	Position map_4_pos(520, 550);

	temp_ent = button_spawner.Spawn(map_1_pos, map_1);
	scene_.push_back(temp_ent);

	temp_ent = button_spawner.Spawn(map_2_pos, map_2);
	scene_.push_back(temp_ent);

	temp_ent = button_spawner.Spawn(map_3_pos, map_3);
	scene_.push_back(temp_ent);

	temp_ent = button_spawner.Spawn(map_4_pos, map_4);
	scene_.push_back(temp_ent);


	// вводить ip и получить название карты
	// получить entity id 
	setStateArgument(std::string("Maps/lvl1.txt"));
	Game::getInstance().setMyEntityId(2);

	for (int i = 0; i < 4; ++i) {
		Game::getInstance().setHullType(i, tank_hull_1);
		Game::getInstance().setTurretType(i, tank_turret_1);
	}
}

GameStateId SinglePlayerMenuGameState::update(sf::RenderWindow& window) {

	Input input;
	input.handleInput(window);

	int chosen_button_id = 0;
	for (int i = 0; i < systems_.size(); ++i) {
		int sys_output = systems_[i]->update(window, scene_);
		if (sys_output) {
			chosen_button_id = sys_output;
		}
	}



	if (input.mouse_click_) {
		switch (chosen_button_id)
		{
		case play_button_id:
			return GameStateId::SinglePlaying;
			break;
		case tank_hull_1_button_id:
			setTankHull(tank_hull_1);
			break;
		case tank_hull_2_button_id:
			setTankHull(tank_hull_2);
			break;
		case tank_turret_1_button_id:
			setTankTurret(tank_turret_1);
			break;
		case tank_turret_2_button_id:
			setTankTurret(tank_turret_2);
			break;
		case back_button_id:
			return GameStateId::MainMenu;
			break;
		case map_2_button_id:
			setStateArgument(std::string("Maps/lvl2.txt"));
			break;
		case map_3_button_id:
			setStateArgument(std::string("Maps/lvl3.txt"));
			break;
		case map_4_button_id:
			setStateArgument(std::string("Maps/lvl4.txt"));
			break;
		default:
			return id_;
			break;
		}
	}

	return id_;
}

