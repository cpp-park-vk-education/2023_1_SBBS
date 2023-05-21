#pragma once
#include "SpawnerSystem.h"
#include "GraphicsComponent.h"
#include "PositionComponent.h"
#include "SoundComponent.h"
#include "ShootComponent.h"
#include "Types.h"
#include <SFML/Graphics.hpp>

Entity* TurretSpawner::Spawn(Position position, char subType) {
	static sf::Image img;//// почему статик???
	sf::SoundBuffer buffer;

	GraphicsComponent* graph_to_add = new GraphicsComponent();
	PositionComponent* pos_to_add = new TurretPositionComponent();
	//SoundComponent* sound_to_add = new SoundComponent();
	ShootComponent* shoot_to_add = new ShootComponent();
	Position pos_struc_to_add(position.x, position.y);
	pos_to_add->setPosition(pos_struc_to_add);


	Entity* to_add = new Entity(ObjectType::Turret);

	graph_to_add = new GraphicsComponent();

	pos_to_add->setPosition(pos_struc_to_add);

	switch (subType)
	{
	case '1': // tank type 1
		img.loadFromFile("Image/tank_1_gun_100_100.png");
		graph_to_add->setAliveImage(img);
		shoot_to_add->setCooldown(1.0);///////// выставить в зависимости от типа 
		////
		//buffer.loadFromFile("Sound/Shot1.wav");
		//sound_to_add->setSound(SoundType::ShootingSound, buffer);
		////
		break;

	case '2': // tank type 1
		img.loadFromFile("Image/tank_2_gun_100_100.png");
		graph_to_add->setAliveImage(img);
		shoot_to_add->setCooldown(1.0);
		break;

	default:
		break;
	}

	graph_to_add->layer = true;
	to_add->putComponent(ComponentID::ShootComponent, shoot_to_add);
	to_add->putComponent(ComponentID::GraphicsComponent, graph_to_add);
	to_add->putComponent(ComponentID::PositionComponent, pos_to_add);
	//to_add->putComponent(ComponentID::SoundComponent, sound_to_add);
	return to_add;
}
