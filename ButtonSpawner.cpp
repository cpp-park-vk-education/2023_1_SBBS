#pragma once
#include "SpawnerSystem.h"
#include "GraphicsComponent.h"
#include "PositionComponent.h"
#include "ClickComponent.h"
#include <fstream>
#include <vector>

Entity* ButtonSpawner::Spawn(Position position, char subType) {
	int height = 150;
	int width = 700;

	Entity* to_add = new Entity(ObjectType::Button);

	GraphicsComponent* graph_to_add = new GraphicsComponent();
	PositionComponent* pos_to_add = new PositionComponent();
	ClickComponent* click_to_add = new ClickComponent(position.x, position.y, width, height);

	Position pos_struc_to_add(position.x, position.y);
	pos_to_add->setPosition(pos_struc_to_add);

	sf::Image img;

	switch (subType) {
		case('h'): // host game button
			img.loadFromFile("Image/GUI_host_game.png");
			graph_to_add->setAliveImage(img);
			click_to_add->setButtonId(1);
			break;

		case('c'): //connect to game button
			img.loadFromFile("Image/GUI_connect_game.png");
			graph_to_add->setAliveImage(img);
			click_to_add->setButtonId(2);
			break;

		case 'b':  // back button
			img.loadFromFile("Image/GUI_back_button.png");
			graph_to_add->setAliveImage(img);
			click_to_add->setButtonId(3);
			break;

		case 's':  // single game button
			img.loadFromFile("Image/GUI_single_game_button.png");
			graph_to_add->setAliveImage(img);
			click_to_add->setButtonId(4);
			break;

		default: break;
	}


	to_add->putComponent(ComponentID::ClickComponent, click_to_add);
	to_add->putComponent(ComponentID::GraphicsComponent, graph_to_add);
	to_add->putComponent(ComponentID::PositionComponent, pos_to_add);
	return to_add;
}