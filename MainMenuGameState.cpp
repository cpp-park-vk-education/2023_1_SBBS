#pragma once
#include "MenuSystem.h"
#include "GameState.h"
#include "SpawnerSystem.h"
#include "Component.h"
#include "InputHandler.h"

MainMenuGameState::MainMenuGameState() {
	/// спавн менюшки реализовать тут 
}

GameState* MainMenuGameState::update(sf::RenderWindow& window) {

	int chosen_button_id = 1;
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
			return new HostMenuGameState;
			break;
		case 2:
			return new ClientMenuGameState;
		default:
			return this;
			break;
		}
	}

	return this;
}

