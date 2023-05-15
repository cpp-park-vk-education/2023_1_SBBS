#pragma once
#include "MenuSystem.h"
#include "GameState.h"
#include "SpawnerSystem.h"
#include "Component.h"
#include "InputHandler.h"
#include "GraphicsSystem.h"

MainMenuGameState::MainMenuGameState() {
	/// спавн менюшки реализовать тут 
	BannerSpawner banner_spawner;
	ButtonSpawner button_spawner;

	//Спавн фона главного меню
	Position banner_pos;
	banner_pos.x = 0;
	banner_pos.y = 0;

	Entity banner_ent;

	banner_ent = banner_spawner.Spawn(banner_pos, 'm');
	banner_ent.setEntityID(1);

	scene_.push_back(banner_ent);
	addSystem(SystemId::MenuSystemId, new MenuSystem);
	addSystem(SystemId::GraphicsSystemId, new GraphicsSystem);

	//Спавн кнопки host game главного меню
	Position host_game_pos;
	host_game_pos.x = 300;  //Над координатами надо думать в зависимости от размера кнопки
	host_game_pos.y = 500;

	Entity host_game_ent;

	host_game_ent = button_spawner.Spawn(banner_pos, 'h');
	host_game_ent.setEntityID(1);

	scene_.push_back(host_game_ent);
	addSystem(SystemId::MenuSystemId, new MenuSystem);
	addSystem(SystemId::GraphicsSystemId, new GraphicsSystem);

	//Спавн кнопки connect to game главного меню
	Position connect_game_pos;
	connect_game_pos.x = 600;  //Над координатами надо думать в зависимости от размера кнопки
	connect_game_pos.y = 500;

	Entity connect_game_ent;

	connect_game_ent = button_spawner.Spawn(banner_pos, 'c');
	connect_game_ent.setEntityID(1);

	scene_.push_back(connect_game_ent);
	addSystem(SystemId::MenuSystemId, new MenuSystem);
	addSystem(SystemId::GraphicsSystemId, new GraphicsSystem);
}



GameState* MainMenuGameState::update(sf::RenderWindow& window) {

	static int chosen_button_id = 1;
	Input input;
	input.handleInput(window);
	chosen_button_id += input.moving_down_;
	chosen_button_id -= input.moving_up_;

	getSystemById(SystemId::GraphicsSystemId)->update(window, scene_);

	MenuSystem ms;

	int mouce_choose = ms.update(window,scene_);
	if (mouce_choose) {
		chosen_button_id = mouce_choose;
	}

	if (input.shoot_) {
		switch (chosen_button_id)
		{
		case 1:
			return new HostMenuGameState();
			break;
		case 2:
			return new ClientMenuGameState();
		default:
			return this;
			break;
		}
	}

	return this;
}

