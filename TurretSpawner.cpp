#pragma once
#include "SpawnerSystem.h"
#include "GraphicsComponent.h"
#include "PositionComponent.h"
#include "Types.h"
#include <SFML/Graphics.hpp>

Entity TurretSpawner::Spawn(Position position, char subType) {
	static sf::Image img;

	GraphicsComponent* graph_to_add = new GraphicsComponent();
	PositionComponent* pos_to_add = new PositionComponent();
	Position pos_struc_to_add(position.x, position.y);
	pos_to_add->setPosition(pos_struc_to_add);


	Entity to_add(ObjectType::Turret);

	graph_to_add = new GraphicsComponent();
	PositionComponent* turr_pos_to_add = new PositionComponent();

	turr_pos_to_add->setPosition(pos_struc_to_add);

	switch (subType)
	{
	case '1': // tank type 1
		img.loadFromFile("Image/tank_1_gun_100_100.png");
		graph_to_add->setImage(img);
		break;

	case '2': // tank type 1
		img.loadFromFile("Image/tank_2_gun_100_100.png");
		graph_to_add->setImage(img);
		break;

	default:
		break;
	}

	graph_to_add->layer = true;
	to_add.putComponent(ComponentID::GraphicsComponent, graph_to_add);
	to_add.putComponent(ComponentID::PositionComponent, turr_pos_to_add);

	return to_add;
}
