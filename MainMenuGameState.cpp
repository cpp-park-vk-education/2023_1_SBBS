#pragma once
#include "MenuSystem.h"
#include "GameState.h"
#include "SpawnerSystem.h"
#include "Component.h"
#include "InputHandler.h"

GameState* MainMenuGameState::update(sf::RenderWindow& window) {
	//on enter generate menu
	std::vector<Entity> scene;

	int chosen_button_id = 1;
	Input input;
	input.handleInput(window);
	chosen_button_id += input.moving_down_;
	chosen_button_id -= input.moving_up_;

	MenuSystem ms;

	int mouce_choose = ms.surfMenu(scene, window);
	if (mouce_choose) {
		chosen_button_id = mouce_choose;
	}


	switch (chosen_button_id)
	{
	default:
		break;
	}

	return this;
}

