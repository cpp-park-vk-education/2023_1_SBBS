#pragma once
#include "MenuSystem.h"
#include "GameState.h"
#include "SpawnerSystem.h"
#include "Component.h"
#include "InputHandler.h"

MainMenuGameState::MainMenuGameState() {
	/// спавн менюшки реализовать тут 
	BannerSpawner banner_spawner;
	ButtonSpawner button_spawner;

	Position banner_pos;
	banner_pos.x = 0;
	banner_pos.y = 0;

	Entity banner_ent;

	banner_ent = banner_spawner.Spawn(banner_pos, 'm');
	banner_ent.setEntityID(1);

	scene_.push_back(banner_ent);
	addSystem(SystemId::MenuSystemId, new MenuSystem);
}

GameState* MainMenuGameState::update(sf::RenderWindow& window) {

	static int chosen_button_id = 1;
	Input input;
	input.handleInput(window);
	chosen_button_id += input.moving_down_;
	chosen_button_id -= input.moving_up_;

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

