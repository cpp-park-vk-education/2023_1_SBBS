#pragma once
#include "MenuSystem.h"
#include "GameState.h"
#include "SpawnerSystem.h"
#include "Component.h"
#include "InputHandler.h"
#include "GraphicsSystem.h"

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

	Entity* banner_ent = new Entity;

	banner_ent = banner_spawner.Spawn(banner_pos, 'm');
	banner_ent->setEntityID(1);

	scene_.push_back(banner_ent);
	addSystem(SystemId::MenuSystemId);
	addSystem(SystemId::GraphicsSystemId);
	addSystem(SystemId::MusicSystemId);


	//Спавн кнопки host game главного меню
	Position host_game_pos;
	host_game_pos.x = 200;  //Над координатами надо думать в зависимости от размера кнопки
	host_game_pos.y = 800;

	Entity* host_game_ent;

	host_game_ent = button_spawner.Spawn(host_game_pos, 'h');
	host_game_ent->setEntityID(1);

	scene_.push_back(host_game_ent);

	//Спавн кнопки connect to game главного меню
	Position connect_game_pos;
	connect_game_pos.x = 1400;  //Над координатами надо думать в зависимости от размера кнопки
	connect_game_pos.y = 800;

	Entity* connect_game_ent;

	connect_game_ent = button_spawner.Spawn(connect_game_pos, 'c');
	connect_game_ent->setEntityID(1);

	scene_.push_back(connect_game_ent);

	// Спавн кнопки одиночной игры
	Position single_game_button_pos;
	single_game_button_pos.x = 800;  //Над координатами надо думать в зависимости от размера кнопки
	single_game_button_pos.y = 500;

	Entity* single_game_button_ent;

	single_game_button_ent = button_spawner.Spawn(single_game_button_pos, 's');
	single_game_button_ent->setEntityID(1);

	scene_.push_back(single_game_button_ent);
}



GameStateId MainMenuGameState::update(sf::RenderWindow& window) {

	static int chosen_button_id = 0;
	Input input;
	input.handleInput(window);
	//chosen_button_id += input.moving_down_;
	//chosen_button_id -= input.moving_up_;

	for (int i = 0; i < systems_.size(); ++i) {
		systems_[i]->update(window, scene_);
	}

	MenuSystem ms;/// тут исправить 

	int mouce_choose = ms.update(window,scene_);
	if (mouce_choose) {
		chosen_button_id = mouce_choose;
		//std::cout << "Chosen button id:" << chosen_button_id << std::endl;
	}

	if (input.shoot_) {
		switch (chosen_button_id)
		{
		case 1:
			return GameStateId::HostPlaying;
			break;
		case 2:
			return GameStateId::ClientPlaying;
		default:
			return id_;
			break;
		}
	}

	return id_;
}

