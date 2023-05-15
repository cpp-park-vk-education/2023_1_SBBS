#pragma once
#include "SpawnerSystem.h"
#include "GraphicsComponent.h"
#include "PositionComponent.h"
#include "ClickComponent.h"
#include <fstream>
#include <vector>

Entity ButtonSpawner::Spawn(Position position, char subType) {
	int height = 100;
	int width = 400;

	Entity to_add(ObjectType::Button);

	GraphicsComponent* graph_to_add = new GraphicsComponent();
	PositionComponent* pos_to_add = new PositionComponent();
	ClickComponent* click_to_add = new ClickComponent(position.x - int(height / 2), position.y - int(width / 2), width, height);

	Position pos_struc_to_add(position.x, position.y);
	pos_to_add->setPosition(pos_struc_to_add);

	sf::Image img;

	switch (subType) {
		case('h'): // host game button
			img.loadFromFile(/*'"Image/GUI_host_game.png"*/"Image/tank_1_body_100_100.png");  //Этого файла еще нет
			graph_to_add->setImage(img);
			break;
		case('c'): //connect to game button
			img.loadFromFile(/*"Image/GUI_connect_game.png"*/"Image/tank_1_body_100_100.png");  //Этого файла еще нет
			graph_to_add->setImage(img);
	}


	to_add.putComponent(ComponentID::ClickComponent, click_to_add);
	to_add.putComponent(ComponentID::GraphicsComponent, graph_to_add);
	to_add.putComponent(ComponentID::PositionComponent, pos_to_add);
	return to_add;
}