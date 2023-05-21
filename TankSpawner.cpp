#pragma once
#include "SpawnerSystem.h"
#include "GraphicsComponent.h"
#include "PositionComponent.h"
#include "CollisionComponent.h"
#include "SoundComponent.h"
#include "HealthComponent.h"
#include "Types.h"
#include <SFML/Graphics.hpp>
#include <fstream>


Entity* TankSpawner::Spawn(Position position, char subType) {

	Entity* to_add = new Entity(ObjectType::Tank);
	sf::SoundBuffer buffer;
	static sf::Image img; /// почему статик?

	PositionComponent* pos_to_add = nullptr;

	switch (current_type_)
	{
	case OwnerType::Network:
		pos_to_add = new NetTurretPositionComponent();
		break;
	case OwnerType::Bot:
		pos_to_add = new BotTurretPositionComponent();
		break;
	case OwnerType::Player:
		pos_to_add = new TurretPositionComponent();
		break;
	default:
		break;
	}

	GraphicsComponent* graph_to_add = new GraphicsComponent();
	CollisionComponent* coll_to_add =  new CollisionComponent(position, 0, 50, 50);
	HealthComponent* health_to_add = new HealthComponent(true, true,true,to_add, 100); //////////// разные танки имеют разное зддоровье
	SoundComponent* sound_to_add = new SoundComponent();

	Position pos_struc_to_add(position.x, position.y);
	pos_to_add->setPosition(pos_struc_to_add);

	switch (subType)
	{
	case '1': // tank type 1
		img.loadFromFile("Image/tank_1_body_100_100.png");
		buffer.loadFromFile("Sound/Engine1.wav");
		sound_to_add->setSound(SoundType::RunnungSound, buffer);
		graph_to_add->setAliveImage(img);
		break;

	case '2': // tank type 2
		img.loadFromFile("Image/tank_2_body_100_100.png");
		graph_to_add->setAliveImage(img);
		break;

	default:
		break;
	}

	
	pos_to_add->setSpeed(7);///// скорость по типу, перебросить в свич
	graph_to_add->layer = true;
	to_add->putComponent(ComponentID::SoundComponent, sound_to_add);
	to_add->putComponent(ComponentID::HealthComponent, health_to_add);
	to_add->putComponent(ComponentID::CollisionComponent, coll_to_add);
	to_add->putComponent(ComponentID::GraphicsComponent, graph_to_add);
	to_add->putComponent(ComponentID::PositionComponent, pos_to_add);
	return to_add;
}
