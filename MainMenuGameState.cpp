#pragma once
#include "MenuSystem.h"
#include "GameState.h"
#include "SpawnerSystem.h"
#include "Component.h"
#include "InputHandler.h"
#include "GraphicsSystem.h"
#include "ButtonID.h"

// on enter()<- создание всех обхъекты на сцене 

MainMenuGameState::MainMenuGameState() {

	id_ = GameStateId::MainMenu;
	/// спавн менюшки реализовать тут 
	BannerSpawner banner_spawner;
	ButtonSpawner button_spawner;


	//Спавн фона главного меню
	Position banner_pos;
	banner_pos.x = 0;
	banner_pos.y = 0;

	Entity* banner_ent = nullptr;

	banner_ent = banner_spawner.Spawn(banner_pos, 'm');//// это кто? убрать магическую константу
	banner_ent->setEntityID(1);

	scene_.push_back(banner_ent);
	addSystem(SystemId::MenuSystemId);
	addSystem(SystemId::GraphicsSystemId);
	addSystem(SystemId::MusicSystemId);
	addSystem(SystemId::MenuSystemId);

	//Спавн кнопки host game главного меню
	Position host_game_pos;
	host_game_pos.x = 200;  //Над координатами надо думать в зависимости от размера кнопки
	host_game_pos.y = 800;

	Entity* host_game_ent;

	host_game_ent = button_spawner.Spawn(host_game_pos,host_game);
	host_game_ent->setEntityID(1);

	scene_.push_back(host_game_ent);

	//Спавн кнопки connect to game главного меню
	Position connect_game_pos;
	connect_game_pos.x = 1400;  //Над координатами надо думать в зависимости от размера кнопки
	connect_game_pos.y = 800;

	Entity* connect_game_ent;

	connect_game_ent = button_spawner.Spawn(connect_game_pos, client_game);
	connect_game_ent->setEntityID(1);

	scene_.push_back(connect_game_ent);

	// Спавн кнопки одиночной игры
	Position single_game_button_pos;
	single_game_button_pos.x = 800;  //Над координатами надо думать в зависимости от размера кнопки
	single_game_button_pos.y = 500;

	Entity* single_game_button_ent;

	single_game_button_ent = button_spawner.Spawn(single_game_button_pos, single_game);
	single_game_button_ent->setEntityID(1);

	scene_.push_back(single_game_button_ent);
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

