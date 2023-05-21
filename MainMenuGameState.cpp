#pragma once
#include "MenuSystem.h"
#include "GameState.h"
#include "SpawnerSystem.h"
#include "Component.h"
#include "InputHandler.h"
#include "GraphicsSystem.h"
#include "ButtonID.h"
#include "BannerID.h"

// on enter()<- создание всех обхъекты на сцене 

MainMenuGameState::MainMenuGameState() {

	id_ = GameStateId::MainMenu;
	/// спавн менюшки реализовать тут 
	BannerSpawner banner_spawner;
	ButtonSpawner button_spawner;


	//Спавн фона главного меню
	Position banner_pos(0, 0);

	Entity* temp_ent = nullptr;

	temp_ent = banner_spawner.Spawn(banner_pos, main_banner);//// это кто? убрать магическую константу
	temp_ent->setEntityID(1);

	scene_.push_back(temp_ent);
	addSystem(SystemId::MenuSystemId);
	addSystem(SystemId::GraphicsSystemId);
	addSystem(SystemId::MusicSystemId);
	addSystem(SystemId::MenuSystemId);

	//Спавн кнопки host game главного меню
	Position host_game_pos(200, 800);

	temp_ent = button_spawner.Spawn(host_game_pos,host_game);
	temp_ent->setEntityID(1);

	scene_.push_back(temp_ent);

	//Спавн кнопки connect to game главного меню
	Position connect_game_pos(1400, 800);

	temp_ent = button_spawner.Spawn(connect_game_pos, client_game);
	temp_ent->setEntityID(1);

	scene_.push_back(temp_ent);

	// Спавн кнопки одиночной игры
	Position single_game_button_pos(800, 800);

	temp_ent = button_spawner.Spawn(single_game_button_pos, single_game);
	temp_ent->setEntityID(1);

	scene_.push_back(temp_ent);
}

GameStateId MainMenuGameState::update(sf::RenderWindow& window) {

	Input input;
	input.handleInput(window);
	// ввод в меню с кнопок пока отложим
	//static int chosen_button_id = 0;
	//chosen_button_id += input.moving_down_;
	//chosen_button_id -= input.moving_up_;
	int chosen_button_id = 0;

	for (int i = 0; i < systems_.size(); ++i) {
		int sys_output = systems_[i]->update(window, scene_);// будет ненулевым только в menusystem
		if (sys_output) {
			chosen_button_id = sys_output;
			//std::cout << "Chosen button id:" << chosen_button_id << std::endl;
		}
	}

	if (input.shoot_) {  ////////////////////////////// shoot не понятно, поменять на mouce click
		switch (chosen_button_id)
		{
		case host_game_button_id:
			return GameStateId::HostMenu;
			break;
		case client_game_button_id:
			return GameStateId::ClientMenu;
			break;
		case single_game_button_id:
			return GameStateId::SingleMenu;
			break;
		default:
			return id_;
			break;
		}
	}

	return id_;
}

