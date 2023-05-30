#pragma once
#include "MenuSystem.h"
#include "ClickComponent.h"
#include <iostream>


int MenuSystem::update(sf::RenderWindow& window, std::vector<Entity*>& scene) {
	int chosen_button_id = 0;
	for (int i = 0; i < scene.size(); ++i) {

		ClickComponent* current_button = dynamic_cast<ClickComponent*>(scene[i]->getComponentByID(ComponentID::ClickComponent));
		if (current_button) {
			if (current_button->isChosen(window)) {
				chosen_button_id = current_button->getButtonId();
				sf::Cursor curs;
				curs.loadFromSystem(sf::Cursor::Hand);
				window.setMouseCursor(curs);
				return chosen_button_id;
			}
		}
	}
	sf::Cursor curs;
	curs.loadFromSystem(sf::Cursor::Arrow);
	window.setMouseCursor(curs);
	return chosen_button_id;
}